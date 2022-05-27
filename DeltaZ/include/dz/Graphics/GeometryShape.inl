inline size_t GeometryShape::getVertexCount() const noexcept
{
   return m_vertices.size();
}

inline zg::Vertex const* GeometryShape::getVertex(size_t index) const noexcept
{
   return &m_vertices.at(index);
}

inline size_t GeometryShape::getElementCount() const noexcept
{
   return m_elements.size();
}

inline unsigned int const* GeometryShape::getElements() const noexcept
{
   return m_elements.data();
}

inline float GeometryShape::getMinValue() const noexcept
{
   return m_minValue;
}

inline float GeometryShape::getMaxValue() const noexcept
{
   return m_maxValue;
}

