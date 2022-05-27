#ifndef NODE_HPP
#define NODE_HPP

#include <zucchini/zucchini.hpp>
#include <glm/glm.hpp>

class Node
{
public:
   struct Neighbours
   {
      Neighbours()
         : up(nullptr), down(nullptr), left(nullptr), right(nullptr),
           leftUp(nullptr), rightUp(nullptr), leftDown(nullptr), rightDown(nullptr) {}

      Node const* up;
      Node const* down;
      Node const* left;
      Node const* right;
      Node const* leftUp;
      Node const* rightUp;
      Node const* leftDown;
      Node const* rightDown;
   };

   void setPosition(glm::vec2 pos) noexcept;
   void setValue(float value) noexcept;
   void setNeighbours(Neighbours neighbours) noexcept;
   void setBoundary(bool boundary = true) noexcept;

   glm::vec2 getPosition() const noexcept;
   float getValue() const noexcept;
   Neighbours& getNeighbours() noexcept;
   Neighbours const& getNeighbours() const noexcept;
   bool isBoundary() const noexcept;

   explicit Node(glm::vec2 pos = {}, float value = 0.f);

private:
   glm::vec2 m_pos;
   float m_value;
   Neighbours m_neighbours;
   bool m_isBoundary;
};

#include "Node.inl"

#endif // NODE_HPP

