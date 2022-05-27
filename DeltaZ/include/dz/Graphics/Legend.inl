inline size_t Legend::getVertexCount() const noexcept
{
   return 4;
}

inline zg::Vertex const* Legend::getVertex(size_t index) const noexcept
{
   ZE_ASSERT(index <= getVertexCount(), "Out of bound !");
   return &m_vertices[index];
}

inline size_t Legend::getElementCount() const noexcept
{
   return 6;
}

inline unsigned int const* Legend::getElements() const noexcept
{
   static unsigned int elements[] = { 0, 1, 2,
                                      2, 3, 0 };
   return elements;
}

