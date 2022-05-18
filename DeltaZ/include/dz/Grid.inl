inline GridNode::Neighbours const& GridNode::getNeighbours() const noexcept
{
   return m_neighbours;
}

inline GridNode& Grid::getNode(int const x, int const y)
{
   return m_domainNodes.at(std::tie(x, y));
}

inline GridNode const& Grid::getNode(int const x, int const y) const
{
   return m_domainNodes.at(std::tie(x, y));
}

inline Node& Grid::getBoundary(int const column, int const index)
{
   return m_boundaries.at(std::tie(column, index));
}

inline Node const& Grid::getBoundary(int const column, int const index) const
{
   return m_boundaries.at(std::tie(column, index));
}

inline std::map<std::tuple<int, int>, GridNode>& Grid::getNodes() noexcept
{
   return m_domainNodes;
}

inline std::map<std::tuple<int, int>, Node>& Grid::getBoundaries() noexcept
{
   return m_boundaries;
}

