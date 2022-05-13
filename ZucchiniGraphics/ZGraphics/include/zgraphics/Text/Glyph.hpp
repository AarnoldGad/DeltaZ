/**
 * Glyph.hpp
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
#ifndef ZG_GLYPH_HPP
#define ZG_GLYPH_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Renderer/Texture.hpp"

namespace zg
{
   class ZG_API Glyph
   {
   public:
      Texture const* getTexture() const noexcept;
      glm::vec4 getRect() const noexcept;
      glm::ivec2 getSize() const noexcept;
      glm::ivec2 getBearing() const noexcept;
      uint32_t getAdvance() const noexcept;

      Glyph(Texture const* texture, glm::vec4 rect, glm::ivec2 size, glm::ivec2 bearing, uint32_t advance);
      Glyph();

   private:
      Texture const* m_texture;
      glm::vec4 m_rect;
      glm::ivec2 m_size;
      glm::ivec2 m_bearing;
      uint32_t m_advance;
   };
}

#include "Glyph.inl"

#endif // ZG_GLYPH_HPP

