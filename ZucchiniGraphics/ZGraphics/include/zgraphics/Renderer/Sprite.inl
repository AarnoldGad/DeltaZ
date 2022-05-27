inline glm::vec2 zg::Sprite::getSize() const noexcept
{
   return m_size;
}

inline glm::vec4 zg::Sprite::getColor() const noexcept
{
   return m_color;
}

inline glm::vec4 zg::Sprite::getTextureRect() const noexcept
{
   return m_textureRect;
}

inline size_t zg::Sprite::getVertexCount() const noexcept
{
   return sizeof(m_vertices) / sizeof(Vertex2D);
}

inline zg::Vertex const* zg::Sprite::getVertex(size_t index) const noexcept
{
   ZE_ASSERT(index <= getVertexCount(), "Out of bound !");
   return &m_vertices[index];
}

inline size_t zg::Sprite::getElementCount() const noexcept
{
   return 6;
}

inline unsigned int const* zg::Sprite::getElements() const noexcept
{
   static unsigned int elements[] = { 0, 1, 2,
                                      1, 2, 3 };
   return elements;
}

inline size_t zg::Sprite::getTextureCount() const noexcept
{
   return m_texture ? 1 : 0;
}

inline zg::Texture const* zg::Sprite::getTexture(size_t index) const noexcept
{
   return m_texture;
}
