/**
 * Font.hpp
 * 18 Nov 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZG_FONT_HPP
#define ZG_FONT_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Text/Glyph.hpp"
#include "zgraphics/Text/Encoding.hpp"

namespace zg
{
   using FontFile = ze::NamedType<std::filesystem::path, struct FontFileParameter,
                                  ze::Dereferenceable, ze::ImplicitlyConvertible>;
   using BitmapFile = ze::NamedType<std::filesystem::path, struct FontFileParameter,
                                    ze::Dereferenceable, ze::ImplicitlyConvertible>;

   // TODO Encoding is currently mostly unsupported and bitmap fonts are mostly limited to one plane
   // with no glyph informations but main design seems ok for now.
   // I will later use Signed Distance Fields and rework the whole system
   class ZG_API Font
   {
   public:
      Status loadFile(FontFile const& file, unsigned short charSize, Encoding encoding = Encoding::Latin1);
      Status loadFile(BitmapFile const& file, glm::ivec2 glyphCount,
                      uint32_t startChar = 32, Encoding encoding = Encoding::Latin1);
      Status loadBitmap(zg::Image const& bitmap, glm::ivec2 glyphCount,
                        uint32_t startChar = 32, Encoding encoding = Encoding::Latin1);

      void unload();

      Glyph const& getGlyph(uint32_t charcode) const;
      Texture const* getAtlas(uint32_t plane) const;

      Encoding getEncoding() const noexcept;
      //void setEncoding(Encoding encoding) noexcept;

      Font();

   private:
      std::map<uint32_t, Glyph> m_glyphs;
      std::map<uint32_t, std::unique_ptr<Texture> > m_atlas;

      Encoding m_encoding;
   };
}

template<>
struct ze::ResourceLoader<zg::Font>
{
public:
   // TODO Return unique_ptr
   static zg::Font* Load(zg::FontFile const& file, unsigned short charSize, zg::Encoding encoding = zg::Encoding::Latin1);
   static zg::Font* Load(zg::BitmapFile const& file, glm::ivec2 glyphCount,
                         uint32_t startChar = 32, zg::Encoding encoding = zg::Encoding::Latin1);
   static zg::Font* Load(zg::Image const& bitmap, glm::ivec2 glyphCount,
                         uint32_t startChar = 32, zg::Encoding encoding = zg::Encoding::Latin1);

   static void Reload(zg::Font* font, zg::FontFile const& file, unsigned short charSize,
                      zg::Encoding encoding = zg::Encoding::Latin1);
   static void Reload(zg::Font* font, zg::BitmapFile const& file, glm::ivec2 glyphCount,
                      uint32_t startChar = 32, zg::Encoding encoding = zg::Encoding::Latin1);
   static void Reload(zg::Font* font, zg::Image const& bitmap, glm::ivec2 glyphCount,
                      uint32_t startChar = 32, zg::Encoding encoding = zg::Encoding::Latin1);

   static void Unload(zg::Font* font);
};

#include "Font.inl"

#endif // ZG_FONT_HPP
