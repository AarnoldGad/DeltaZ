#include "zgpch.hpp"

#include "zgraphics/Renderer/Vertex2D.hpp"

namespace zg
{
   Vertex2D::Vertex2D(glm::vec2 pos, glm::vec4 color, glm::vec2 uv)
      : m_pos(pos), m_color(color), m_uv(uv) {}

   void const* Vertex2D::getData(unsigned int location) const noexcept
   {
      switch (location)
      {
         case 0:
            return glm::value_ptr(m_pos);
         case 1:
            return glm::value_ptr(m_color);
         case 2:
            return glm::value_ptr(m_uv);
         default:
            return nullptr;
      }
   }

   void Vertex2D::setPosition(glm::vec2 pos) noexcept
   {
      m_pos = pos;
   }

   void Vertex2D::setColor(glm::vec4 color) noexcept
   {
      m_color = color;
   }

   void Vertex2D::setTextureCoordinates(glm::vec2 uv) noexcept
   {
      m_uv = uv;
   }
}
