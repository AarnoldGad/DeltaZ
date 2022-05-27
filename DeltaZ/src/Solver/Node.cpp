#include "dz/Solver/Node.hpp"

Node::Node(glm::vec2 const pos, float const value)
      : m_pos(pos), m_value(value), m_neighbours(), m_isBoundary(false) {}

void Node::setPosition(glm::vec2 const pos) noexcept
{
   m_pos = pos;
}

void Node::setValue(float const value) noexcept
{
   m_value = value;
}

void Node::setBoundary(bool const boundary) noexcept
{
   m_isBoundary = boundary;
}

void Node::setNeighbours(Neighbours const neighbours) noexcept
{
   m_neighbours = neighbours;
}

