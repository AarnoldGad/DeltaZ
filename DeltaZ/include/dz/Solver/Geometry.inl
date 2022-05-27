inline Geometry::operator bool() const noexcept
{
   return m_nodes.size();
}

inline float Geometry::getPrecision() const noexcept
{
   return m_precision;
}

inline std::vector<Node>& Geometry::getNodes() noexcept
{
   return m_nodes;
}

inline std::vector<Node> const& Geometry::getNodes() const noexcept
{
   return m_nodes;
}

