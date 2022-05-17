#include "zgraphics/Text/Font.hpp"
#include "detail/Common/ContextImpl.hpp"

#include <glad/glad.h>

#define MAX_FONT_SIZE 1024UL

TODO_BEFORE(6, 2022, "Prove that everything work as expected (No memory leak, no overflow, no errors, etc...)");
namespace zg
{
   namespace
   {
      using Value = ze::NamedType<uint32_t, struct ValueParameter, ze::ImplicitlyConvertible>;
      using Max= ze::NamedType<uint32_t, struct ValueParameter, ze::ImplicitlyConvertible>;

      // TODO Maybe a better algorithm exists
      std::optional<uint32_t> FindFirstBitGreaterThan(Value const value, Max const max = Max(0x80000000))
      {
         if (value > 0x80000000 || value > max) return std::nullopt; // Guard overflow
         
         uint32_t bit = 1;
         while (bit < value) if (bit <<= 1, bit > max) return std::nullopt;
         return bit;
      }

      Status CheckPrerequisites(FT_Library lib, std::filesystem::path const& file, short const charSize)
      {
         if (!lib)
            return ze::Console::Trace("Fail to load font file {} : Freetype has not been loaded yet !", file),
                   Status::Error;
         if (charSize > MAX_FONT_SIZE || charSize == 0)
            return ze::Console::Trace("Invalid font size : {}", charSize),
                   Status::Error;
         
         return Status::OK;
      }

      std::tuple<FT_Error, FT_Face> LoadNewFace(FT_Library lib, std::filesystem::path const& file,
                                                short const charSize, zg::Encoding encoding)
      {
         FT_Face face;
         FT_Error fterror = FT_New_Face(lib, file.string().c_str(), 0, &face);
         if (fterror)
            return ze::Console::Trace("Fail to load font file {}", file),
                   std::make_tuple(fterror, face);

         // TODO Encoding
         if (face->charmap->encoding != FT_Encoding::FT_ENCODING_UNICODE)
            return ze::Console::Trace("Fail to retrieve unicode charmap from font {}", file),
                   std::make_tuple(fterror, face);

         fterror = FT_Set_Pixel_Sizes(face, 0, charSize);
         if (fterror)
            return ze::Console::Trace("Fail to set pixel size for font {}", file),
                   std::make_tuple(fterror, face);

         return std::make_tuple(fterror, face);
      }

      std::tuple<uint32_t, uint8_t*> GeneratePlaneArray(short const charSize)
      {
         uint32_t minimumAtlasSize = charSize * 16;
         auto planeSize= FindFirstBitGreaterThan(Value(minimumAtlasSize), Max(GL_MAX_TEXTURE_SIZE));
         if (!planeSize.has_value())
            return ze::Console::Trace("Invalid atlas size for char size {} !", charSize),
                   std::make_tuple(0, nullptr);

         uint32_t planeByteSize = planeSize.value() * planeSize.value();
         uint8_t* plane = new uint8_t[planeByteSize];
         std::fill(plane, plane + planeByteSize, 0);

         return std::make_tuple(planeSize.value(), plane);
      }

      Status TryLoadChar(FT_Face face, uint32_t const charcode)
      {
         int error = FT_Load_Char(face, charcode, FT_LOAD_RENDER);
         if (error)
            return ze::Console::Print("Fail to load character {:#x} from font {}", charcode, std::string(face->family_name)),
                   Status::Error;
         return Status::OK;
      }

      Status LoadGlyphPlane(FT_Face face, short const charSize, uint32_t const planeID,
                            uint32_t const firstGlyph, uint32_t const lastGlyph,
                            std::map<uint32_t, Glyph>& glyphs,
                            std::map<uint32_t, std::unique_ptr<Texture> >& planes)
      {
         ZE_ASSERT(firstGlyph < lastGlyph, "Invalid character range !");
         ZE_ASSERT(lastGlyph - firstGlyph < 16 * 16, "Plane cannot be more than 16*16 chars !");

         auto [planeSize, plane] = GeneratePlaneArray(charSize);
         if (!plane)
            return ze::Console::Trace("Fail to generate glyph plane {} for font {} !", planeID, std::string(face->family_name)),
                   Status::Error;
         uint32_t boxSize = planeSize / 16;
         std::unique_ptr<Texture> planeTexture = std::make_unique<Texture>();
         auto glyph = face->glyph;

         glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

         for (uint32_t charcode = firstGlyph; charcode < lastGlyph; ++charcode)
         {
            if (TryLoadChar(face, charcode) == Status::Error) continue;

            glm::ivec2 pos = { charcode % 16 * boxSize, charcode / 16 * boxSize - firstGlyph / 16 * boxSize };
            glm::ivec2 size = { glyph->bitmap.width, glyph->bitmap.rows };

            // Copy glyph bitmap at right position in plane
            for (int y = 0; y < size.y; ++y)
               for (int x = 0; x < size.x; ++x)
                  plane[(pos.x + x) + (pos.y + y) * planeSize] = glyph->bitmap.buffer[x + y * glyph->bitmap.pitch];

            glm::vec4 rect = { static_cast<float>(pos.x)  / static_cast<float>(planeSize),
                               static_cast<float>(pos.y)  / static_cast<float>(planeSize),
                               static_cast<float>(size.x) / static_cast<float>(planeSize),
                               static_cast<float>(size.y) / static_cast<float>(planeSize) };
            glyphs[charcode] = Glyph(planeTexture.get(), rect, size,
                                     { glyph->bitmap_left, glyph->bitmap_top },
                                     glyph->advance.x);
         }

         planeTexture->loadData(plane, { planeSize, planeSize }, Image::Format::Grey);
         planes[planeID] = std::move(planeTexture);

         glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

         return Status::OK;
      }
   }

   Font::Font()
      : m_encoding(Encoding::Unkown) {}

   Status Font::loadFile(FontFile const& file, unsigned short const charSize, Encoding const encoding)
   {
      FT_Library lib = details::ContextImpl::GetFreetype();
      if (CheckPrerequisites(lib, file, charSize) == Status::Error) return Status::Error;

      // Init font data
      this->unload();
      m_encoding = encoding;

      auto [error, face] = LoadNewFace(lib, file, charSize, encoding);
      if (error) return Status::Error;

      // Load Characters (ASCII and Latin1)
      if (LoadGlyphPlane(face, charSize, 0, 0x00, 0x7F, m_glyphs, m_atlas) == Status::Error) return Status::Error;
      if (LoadGlyphPlane(face, charSize, 1, 0xA0, 0xFF, m_glyphs, m_atlas) == Status::Error) return Status::Error;

      FT_Done_Face(face);

      return Status::OK;
   }

   TODO_BEFORE(7, 2022, "Implement bitmap fonts");
   Status Font::loadFile(BitmapFile const& file, glm::ivec2 const glyphCount,
                         uint32_t const startChar, Encoding const encoding)
   {
      return Status::OK;
   }

   Status Font::loadBitmap(Image const& bitmap, glm::ivec2 const glyphCount,
                           uint32_t const startChar, Encoding const encoding)
   {
      return Status::OK;
   }

   void Font::unload()
   {
      m_glyphs.clear();
      m_atlas.clear();
      m_encoding = Encoding::Unkown;
   }
}

// TODO Implement
namespace ze
{
   zg::Font* ResourceLoader<zg::Font>::Load(zg::FontFile const& file,
                                            unsigned short const charSize, zg::Encoding const encoding)
   {
      auto foundFile = ze::ResourceManager<zg::Font>::FindFile(file);

      if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file.get()), nullptr;

      zg::Font* font= new zg::Font;
      font->loadFile(zg::FontFile(foundFile.value()), charSize, encoding);
      return font;
   }

   zg::Font* ResourceLoader<zg::Font>::Load(zg::BitmapFile const& file, glm::ivec2 const glyphCount,
                                            uint32_t const startChar, zg::Encoding const encoding)
   {
      auto foundFile = ze::ResourceManager<zg::Font>::FindFile(file);

      if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file.get()), nullptr;

      zg::Font* font= new zg::Font;
      font->loadFile(zg::BitmapFile(foundFile.value()), glyphCount, startChar, encoding);
      return font;
   }

   zg::Font* ResourceLoader<zg::Font>::Load(zg::Image const& bitmap, glm::ivec2 const glyphCount,
                                            uint32_t const startChar, zg::Encoding const encoding)
   {
      zg::Font* font = new zg::Font;
      font->loadBitmap(bitmap, glyphCount, startChar, encoding);
      return font;
   }

   void ResourceLoader<zg::Font>::Reload(zg::Font* const font, zg::FontFile const& file,
                                         unsigned short const charSize, zg::Encoding const encoding)
   {
      auto foundFile = ze::ResourceManager<zg::Font>::FindFile(file);
      if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file.get());
      font->loadFile(zg::FontFile(foundFile.value()), charSize, encoding);
   }

   void ResourceLoader<zg::Font>::Reload(zg::Font* const font, zg::BitmapFile const& file, glm::ivec2 const glyphCount,
                                         uint32_t const startChar, zg::Encoding const encoding)
   {
      auto foundFile = ze::ResourceManager<zg::Font>::FindFile(file);
      if (!foundFile) return (void) ze::Console::Trace("File not found : {}", file.get());
      font->loadFile(zg::BitmapFile(foundFile.value()), glyphCount, startChar, encoding);
   }

   void ResourceLoader<zg::Font>::Reload(zg::Font* const font, zg::Image const& bitmap, glm::ivec2 const glyphCount,
                                         uint32_t const startChar, zg::Encoding const encoding)
   {
      font->loadBitmap(bitmap, glyphCount, startChar, encoding);
   }

   void ResourceLoader<zg::Font>::Unload(zg::Font* const font)
   {
      font->unload();
   }
}

