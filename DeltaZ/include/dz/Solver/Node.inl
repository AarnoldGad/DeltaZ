inline glm::vec2 Node::getPosition() const noexcept
{
   return m_pos;
}

inline float Node::getValue() const noexcept
{
   return m_value;
}

inline bool Node::isBoundary() const noexcept
{
   return m_isBoundary;
}

inline Node::Neighbours& Node::getNeighbours() noexcept
{
   return m_neighbours;
}

inline Node::Neighbours const& Node::getNeighbours() const noexcept
{
   return m_neighbours;
}

