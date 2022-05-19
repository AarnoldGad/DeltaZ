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

   void setBoundary(bool boundary = true) noexcept;
   bool isBoundary() const noexcept;

   void setNeighbours(Neighbours neighbours) noexcept;
   Neighbours const& getNeighbours() const noexcept;

   explicit GridNode(glm::vec2 pos, double value = 0.0)
      : Node(pos, value), m_neighbours(), m_isBoundary(false) {}

private:
   Neighbours m_neighbours;
   bool m_isBoundary;
};

class Grid
{
public:
   void configureGridFrom(Geometry const& geometry);

   float getPrecision() const noexcept;
   glm::vec4 getBounds() const noexcept;
   
   GridNode& getNode(int x, int y);
   GridNode const& getNode(int x, int y) const;

   std::map<std::tuple<int, int>, GridNode>& getNodes() noexcept;
   std::map<std::tuple<int, int>, GridNode> const& getNodes() const noexcept;

   Grid()
      : m_precision{} {}
   
private:
   void setDomainBounds(Geometry const& geometry);
   void generateGridNodes(Geometry const& geometry);
   void findNeighboursAndBoundaries();
   void initBoundaryValues();

   std::optional<GridNode::Neighbours> findNeighbours(int x, int y);

   bool isOnSegment(glm::vec2 point, glm::vec2 a, glm::vec2 b) const;
   bool isCCW(glm::vec2 a, glm::vec2 b, glm::vec2 c) const;
   bool doesSegmentsIntersect(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d) const;
   bool isPointInDomain(glm::vec2 point, glm::vec2 center, std::vector<glm::vec2> const& shape) const;

   // Represent the distance between two nodes
   float m_precision;
   glm::vec4 m_bounds;
   // Index grid nodes by position in grid
   std::map<std::tuple<int, int>, GridNode> m_nodes; // Only the nodes inside of the domain
};

#include "Grid.inl"

#endif // GRID_HPP

