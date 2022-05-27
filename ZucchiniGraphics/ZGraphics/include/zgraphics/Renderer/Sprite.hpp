/**
 * Sprite.hpp
 * 26 Sep 2021
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
#ifndef ZG_SPRITE_HPP
#define ZG_SPRITE_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Renderer/TexturedMesh.hpp"
#include "zgraphics/Renderer/Transform.hpp"
#include "zgraphics/Renderer/Vertex2D.hpp"
#include "zgraphics/Renderer/Texture.hpp"
#include "zgraphics/Common/Colors.hpp"

namespace zg
{
   class ZG_API Sprite : public TexturedMesh, public Transform
   {
   public:
      void setSize(glm::vec2 size) noexcept;
      glm::vec2 getSize() const noexcept;

      void setColor(glm::vec4 color) noexcept;
      glm::vec4 getColor() const noexcept;

      void setTextureRect(glm::vec4 rect) noexcept;
      glm::vec4 getTextureRect() const noexcept;

      size_t getVertexCount() const noexcept override;
      Vertex const* getVertex(size_t index) const noexcept override;

      size_t getElementCount() const noexcept override;
      unsigned int const* getElements() const noexcept override;

      size_t getTextureCount() const noexcept override;
      void setTexture(Texture const* texture) noexcept;
      Texture const* getTexture(size_t index) const noexcept override;
      
      explicit Sprite(glm::vec2 size = {}, Texture const* texture = nullptr,
                      glm::vec4 color = Colors::White, glm::vec4 textureRect = { 0.f, 0.f, 1.f, 1.f });

   private:
      Texture const* m_texture;
      glm::vec2 m_size;
      glm::vec4 m_color;
      glm::vec4 m_textureRect;
      Vertex2D m_vertices[4];
   };
}

#include "Sprite.inl"

#endif /* ZG_SPRITE_HPP */
