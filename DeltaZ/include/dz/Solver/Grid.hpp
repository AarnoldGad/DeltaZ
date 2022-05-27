#ifndef GRID_HPP
#define GRID_HPP

#include "dz/Solver/Geometry.hpp"
#include "dz/Solver/Node.hpp"

#include <zucchini/zucchini.hpp>
#include <glm/glm.hpp>

#include <map>

class Grid
{
public:
   void configureGridFrom(Geometry const& geometry);

   float getPrecision() const noexcept;
   glm::vec4 getBounds() const noexcept;

   Node& getNode(int x, int y);
   Node const& getNode(int x, int y) const;

   std::map<std::tuple<int, int>, Node>& getNodes() noexcept;
   std::map<std::tuple<int, int>, Node> const& getNodes() const noexcept;

   Grid();

private:
   enum class Orientation
   {
      Unknown = 0,
      Clockwise, CounterClockwise, Colinear
   };

   // Grid initialisation
   void setGridBounds(Geometry const& geometry);
   void generateGrid(std::vector<Node> const& closedShape);
   void initNeighbours();
   void initBoundaries(std::vector<Node> const& closedShape);

   Node::Neighbours findNeighbours(int x, int y);

   // Math and geometry helpers
   float interpolate(Node const& point, Node const& segmentStart, Node const& segmentEnd) const;
   bool isPointInShape(glm::vec2 point, std::vector<Node> const& closedShape) const;
   float distanceFromSegment(glm::vec2 point, glm::vec2 segmentStart, glm::vec2 segmentEnd) const;
   bool isOnSegment(glm::vec2 point, glm::vec2 segmentStart, glm::vec2 segmentEnd) const;
   Orientation findOrientation(glm::vec2 a, glm::vec2 b, glm::vec2 c) const;
   bool doesSegmentsIntersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2) const;

   // Represent the distance between two nodes
   float m_precision;
   glm::vec4 m_bounds;
   // Index grid nodes by position in grid
   std::map<std::tuple<int, int>, Node> m_nodes; // Only the nodes inside of the domain
};

#include "Grid.inl"

#endif // GRID_HPP

