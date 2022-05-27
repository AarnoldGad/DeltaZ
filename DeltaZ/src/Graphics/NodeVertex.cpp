#include "dz/Graphics/NodeVertex.hpp"

NodeVertex::NodeVertex(glm::vec2 pos, float value)
   : m_pos(pos), m_value(value) {}

NodeVertex::NodeVertex(Node const& node)
   : m_pos(node.getPosition()), m_value(node.getValue()) {}

void NodeVertex::setPosition(glm::vec2 pos) noexcept
{
   m_pos = pos;
}

void NodeVertex::setValue(float value) noexcept
{
   m_value = value;
}

void const* NodeVertex::getData(unsigned int const location) const noexcept
{
   switch (location)
   {
      case 0:
         return glm::value_ptr(m_pos);
         break;
      case 1:
         return &m_value;
         break;
      default:
         return nullptr;
   }
}

