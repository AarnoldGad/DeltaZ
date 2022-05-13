#include "zgpch.hpp"

#include "zgraphics/Text/Font.hpp"
#include "detail/Common/ContextImpl.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace zg
{
   Font::Font()
      : m_encoding(Encoding::Latin1) {}

   Status Font::loadFile(std::filesystem::path const& file, uint32_t const size, Encoding encoding)
   {
      FT_Library lib = details::ContextImpl::GetFreetype();
      if (!lib)
         return ze::Console::Trace("Fail to load font file {} : Freetype has not been loaded yet", file),
                Status::Error;
      if (size > MAX_FONT_SIZE)
         return ze::Console::Trace("Font size is to big !"), Status::Error;

      // Init font data
      m_size = size;
      m_file = file;
      m_encoding = encoding;

      m_glyphs.clear();

      FT_Face face;

      // TODO Error handling
      int error = FT_New_Face(lib, file.string().c_str(), 0, &face);
      if (error)
         return ze::Console::Trace("Fail to load font file {}", file), Status::Error;

      // TODO Encoding
      if (face->charmap->encoding != FT_Encoding::FT_ENCODING_UNICODE)
         return ze::Console::Trace("Fail to retrieve unicode charmap from font {}", file), Status::Error;

      error = FT_Set_Pixel_Sizes(face, 0, size);
      if (error)
         return ze::Console::Trace("Fail to set pixel size for font {}", file), Status::Error;

      // Load Characters
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      // Generate a 16*8 chars table for ASCII chars
      uint32_t neededRowLength = size * 16;
      uint32_t rowLength = 1;
      while (rowLength <= neededRowLength) rowLength<<= 1;
      uint32_t totalSize = rowLength * rowLength / 2;
      uint8_t* ascii = new uint8_t[totalSize];
      std::fill(ascii, ascii+totalSize, 0);
      uint32_t charSize = rowLength / 16;

      // Ascii Characters
      for (uint32_t charcode = 0x00; charcode < 0x7F; ++charcode)
      {
         error = FT_Load_Char(face, charcode, FT_LOAD_RENDER);
         if (error)
         {
            ze::Console::Print("Fail to load character {:#x} from font {}", charcode, file);
            continue;
         }

         auto glyph = face->glyph;

         glm::ivec2 pos = { charcode % 16 * charSize, charcode / 16 * charSize };
         glm::ivec2 size = { glyph->bitmap.width, glyph->bitmap.rows };

         for (int y = 0; y < size.y; ++y)
            for (int x = 0; x < size.x; ++x)
               ascii[(pos.x + x) + (pos.y + y) * rowLength] = glyph->bitmap.buffer[x + y * glyph->bitmap.pitch];

         glm::vec4 rect = { static_cast<float>(pos.x) / static_cast<float>(rowLength),
                            static_cast<float>(pos.y) * 2.f / static_cast<float>(rowLength),
                            static_cast<float>(size.x) / static_cast<float>(rowLength),
                            static_cast<float>(size.y) * 2.f / static_cast<float>(rowLength) };
         m_glyphs[charcode] = Glyph(&m_ascii, rect, size,
                                    { glyph->bitmap_left, glyph->bitmap_top },
                                    glyph->advance.x);
      }

      m_ascii.loadData(ascii, { rowLength, rowLength / 2 }, Image::Format::Grey);
/*
      // Latin1 Supplement
      for (uint32_t charcode = 0xA0; charcode <= 0xFF; ++charcode)
      {
         error = FT_Load_Char(face, charcode, FT_LOAD_RENDER);
         if (error)
         {
            ze::Console::Print("Fail to load character {:#x} from font {}", charcode, file);
            continue;
         }

         auto glyph = face->glyph;
         zg::Texture* texture = m_textures.emplace(charcode, std::make_unique<Texture>()).first->second.get();
         texture->loadData(glyph->bitmap.buffer, { glyph->bitmap.width, glyph->bitmap.rows }, Image::Format::Grey);
         m_glyphs[charcode] = Glyph(texture,
                                    { glyph->bitmap.width, glyph->bitmap.rows },
                                    { glyph->bitmap_left, glyph->bitmap_top },
                                      glyph->advance.x);
      }*/

      glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
      FT_Done_Face(face);

      return Status::OK;
   }

   void Font::setEncoding(Encoding const encoding) noexcept
   {
      m_encoding = encoding;
   }
}
