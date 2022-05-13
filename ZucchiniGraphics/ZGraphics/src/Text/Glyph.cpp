#include "zgpch.hpp"

#include "zgraphics/Text/Glyph.hpp"

namespace zg
{
   Glyph::Glyph()
      : m_texture(nullptr), m_size{}, m_bearing{}, m_advance{} {}

   Glyph::Glyph(Texture const* texture, glm::vec4 rect, glm::ivec2 const size,
                glm::ivec2 const bearing, uint32_t advance)
      : m_texture(texture), m_rect(rect), m_size(size),
        m_bearing(bearing), m_advance(advance)
   {}
}
