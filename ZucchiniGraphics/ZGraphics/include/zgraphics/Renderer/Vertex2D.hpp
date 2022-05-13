/**
 * Vertex2D.hpp
 * 23 Sep 2021
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
#ifndef ZE_VERTEX2D_HPP
#define ZE_VERTEX2D_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Renderer/Vertex.hpp"

namespace zg
{
   class ZG_API Vertex2D : public Vertex
   {
   public:
      void const* getData(unsigned int location) const noexcept override;

      glm::vec2 getPosition() const noexcept;
      glm::vec4 getColor() const noexcept;
      glm::vec2 getTextureCoordinates() const noexcept;

      void setPosition(glm::vec2 pos) noexcept;
      void setColor(glm::vec4 color) noexcept;
      void setTextureCoordinates(glm::vec2 uv) noexcept;

      explicit Vertex2D(glm::vec2 pos = {}, glm::vec4 color = { 1.f, 1.f, 1.f, 1.f }, glm::vec2 uv = {});

   private:
      glm::vec2 m_pos;
      glm::vec4 m_color;
      glm::vec2 m_uv;
   };
}

#include "Vertex2D.inl"

#endif /* ZE_VERTEX2D_HPP */
