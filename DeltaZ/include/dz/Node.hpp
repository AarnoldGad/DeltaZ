#ifndef NODE_HPP
#define NODE_HPP

#include <zucchini/zucchini.hpp>
#include <glm/glm.hpp>

class Node
{
public:
   void setValue(double value) noexcept;
   double getValue() const noexcept;

   void setPosition(glm::vec2 pos) noexcept;
   glm::vec2 getPosition() const noexcept;

   explicit Node(glm::vec2 pos = {}, double value = 0.0)
      : m_pos(pos), m_value(value) {}

private:
   glm::vec2 m_pos;
   double m_value;
};

#include "Node.inl"

#endif // NODE_HPP

