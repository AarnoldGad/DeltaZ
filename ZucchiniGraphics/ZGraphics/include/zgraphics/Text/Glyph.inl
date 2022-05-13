inline zg::Texture const* zg::Glyph::getTexture() const noexcept
{
   return m_texture;
}

inline glm::vec4 zg::Glyph::getRect() const noexcept
{
   return m_rect;
}

inline glm::ivec2 zg::Glyph::getSize() const noexcept
{
   return m_size;
}

inline glm::ivec2 zg::Glyph::getBearing() const noexcept
{
   return m_bearing;
}

inline uint32_t zg::Glyph::getAdvance() const noexcept
{
   return m_advance;
}
