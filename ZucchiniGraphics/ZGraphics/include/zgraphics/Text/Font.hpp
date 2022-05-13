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
   using FontFile = ze::NamedType<std::filesystem::path, struct FontFileParameter>;
   using BitmapFile = ze::NamedType<std::filesystem::path, struct FontFileParameter>;

   class ZG_API Font
   {
   public:
      static Font* LoadFile(FontFile file, short size, Encoding encoding = Encoding::Latin1);
      static Font* LoadFile(BitmapFile file, Encoding encoding = Encoding::Latin1);
      static Font* LoadBitmap(zg::Image const& bitmap, Encoding encoding = Encoding::Latin1);

      virtual Glyph const& getGlyph(uint32_t charcode) const = 0;

      Encoding getEncoding() const noexcept;
      void setEncoding(Encoding encoding) noexcept;

   private:
      Font();
      ~Font() = default;

      Encoding m_encoding;
   };
}

template<>
struct ze::ResourceLoader<zg::Font>
{
public:
   static zg::Font* Load(zg::FontFile const& file, short size, zg::Encoding encoding = zg::Encoding::Latin1);
   static zg::Font* Load(zg::BitmapFile const& file, zg::Encoding encoding = zg::Encoding::Latin1);
   static zg::Font* Load(zg::Image const& bitmap, zg::Encoding encoding = zg::Encoding::Latin1);

   static void Reload(zg::Font* font, zg::FontFile const& file, short size, zg::Encoding encoding = zg::Encoding::Latin1);
   static void Reload(zg::Font* font, zg::BitmapFile const& file, zg::Encoding encoding = zg::Encoding::Latin1);
   static void Reload(zg::Font* font, zg::Image const& bitmap, zg::Encoding encoding = zg::Encoding::Latin1);

   static void Unload(zg::Font* font);
};

#include "Font.inl"

#endif // ZG_FONT_HPP
