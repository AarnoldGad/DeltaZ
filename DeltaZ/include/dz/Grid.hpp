#ifndef GRID_HPP
#define GRID_HPP

#include <map>
#include <zucchini/zucchini.hpp>
#include <glm/glm.hpp>

#include "dz/Geometry.hpp"
#include "dz/Node.hpp"

class GridNode : public Node
{
public:
   struct Neighbours
   {
      Neighbours()
         : up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}

      Node const* up;
      Node const* down;
      Node const* left;
      Node const* right;
   };

   void setNeighbours(Neighbours neighbours) noexcept;
   Neighbours const& getNeighbours() const noexcept;

   explicit GridNode(glm::ivec2 location, double value = 0.0)
      : Node(static_cast<glm::vec2>(location), value), m_neighbours() {}

private:
   Neighbours m_neighbours;
};

class Grid
{
public:
   void configureGridFrom(Geometry const& geometry);
   
   GridNode& getNode(int x, int y);
   GridNode const& getNode(int x, int y) const;

   Node& getBoundary(int column, int index);
   Node const& getBoundary(int column, int index) const;

   std::map<std::tuple<int, int>, Node>& getBoundaries() noexcept;
   std::map<std::tuple<int, int>, GridNode>& getNodes() noexcept;
   
private:
   // Index boundary nodes by grid column number (left to right) then node number (top to bottom in column)
   std::map<std::tuple<int, int>, Node> m_boundaries;
   // Index grid nodes by position in grid
   std::map<std::tuple<int, int>, GridNode> m_domainNodes; // Only the nodes inside of the domain
};

#include "Grid.inl"

#endif // GRID_HPP

