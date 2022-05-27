inline size_t GridShape::getVertexCount() const noexcept
{
   return m_vertices.size();
}

inline zg::Vertex const* GridShape::getVertex(size_t index) const noexcept
{
   return &m_vertices.at(index);
}

inline size_t GridShape::getElementCount() const noexcept
{
   return m_elements.size();
}

inline unsigned int const* GridShape::getElements() const noexcept
{
   return m_elements.data();
}

