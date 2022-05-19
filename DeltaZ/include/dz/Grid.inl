inline bool GridNode::isBoundary() const noexcept
{
   return m_isBoundary;
}

inline GridNode::Neighbours const& GridNode::getNeighbours() const noexcept
{
   return m_neighbours;
}

inline float Grid::getPrecision() const noexcept
{
   return m_precision;
}

inline glm::vec4 Grid::getBounds() const noexcept
{
   return m_bounds;
}

inline GridNode& Grid::getNode(int const x, int const y)
{
   return m_nodes.at(std::tie(x, y));
}

inline GridNode const& Grid::getNode(int const x, int const y) const
{
   return m_nodes.at(std::tie(x, y));
}

inline std::map<std::tuple<int, int>, GridNode>& Grid::getNodes() noexcept
{
   return m_nodes;
}

inline std::map<std::tuple<int, int>, GridNode> const& Grid::getNodes() const noexcept
{
   return m_nodes;
}

