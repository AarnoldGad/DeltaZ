#include "zgpch.hpp"

#include "zgraphics/Renderer/Sprite.hpp"

namespace zg
{
   Sprite::Sprite(glm::vec2 size, Texture const* texture, glm::vec4 color, glm::vec4 textureRect)
      : m_texture(texture), m_size(size), m_color(color), m_textureRect(textureRect)
   {
      setSize(size);
      setColor(color);
      setTextureRect(textureRect);
   }

   void Sprite::setSize(glm::vec2 size) noexcept
   {
      m_size = size;

      m_vertices[0].setPosition({ 0.f     , 0.f      });
      m_vertices[1].setPosition({ m_size.x, 0.f      });
      m_vertices[2].setPosition({ 0.f     , m_size.y });
      m_vertices[3].setPosition({ m_size.x, m_size.y });
   }

   void Sprite::setColor(glm::vec4 color) noexcept
   {
      m_color = color;

      m_vertices[0].setColor(m_color);
      m_vertices[1].setColor(m_color);
      m_vertices[2].setColor(m_color);
      m_vertices[3].setColor(m_color);
   }

   void Sprite::setTextureRect(glm::vec4 rect) noexcept
   {
      m_textureRect = rect;

      m_vertices[0].setTextureCoordinates({ m_textureRect.x                  , m_textureRect.y                   });
      m_vertices[1].setTextureCoordinates({ m_textureRect.x + m_textureRect.z, m_textureRect.y                   });
      m_vertices[2].setTextureCoordinates({ m_textureRect.x                  , m_textureRect.y + m_textureRect.w });
      m_vertices[3].setTextureCoordinates({ m_textureRect.x + m_textureRect.z, m_textureRect.y + m_textureRect.w });
   }

   void Sprite::setTexture(Texture const* texture) noexcept
   {
      m_texture = texture;
   }
}
