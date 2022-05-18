#include "dz/Node.hpp"

void Node::setValue(double value) noexcept
{
   m_value = value;
}

void Node::setPosition(glm::vec2 pos) noexcept
{
   m_pos = pos;
}

