#include "dz/Grid.hpp"

#include <algorithm>
#include <glm/gtc/epsilon.hpp>

void GridNode::setBoundary(bool boundary) noexcept
{
   m_isBoundary = boundary;
}

void GridNode::setNeighbours(Neighbours neighbours) noexcept
{
   m_neighbours = neighbours;
}

void Grid::configureGridFrom(Geometry const& geometry)
{
   m_precision = geometry.getPrecision();
   
   setDomainBounds(geometry);
   generateGridNodes(geometry);
   findNeighboursAndBoundaries();
   initBoundaryValues();
}

void Grid::setDomainBounds(Geometry const& geometry)
{
   glm::vec4 bounds = { 0.f, 0.f, 0.f, 0.f };
   for (auto const& node : geometry.getNodes())
   {
      if (node.getPosition().x < bounds.x) bounds.x = node.getPosition().x;
      if (node.getPosition().y < bounds.y) bounds.y = node.getPosition().y;
      if (node.getPosition().x > bounds.z) bounds.z = node.getPosition().x;
      if (node.getPosition().y > bounds.w) bounds.w = node.getPosition().y;
   }

   m_bounds = bounds;
}

void Grid::generateGridNodes(Geometry const& geometry)
{
   int columnCount = (m_bounds.z - m_bounds.x) / m_precision + 1;
   int rowCount = (m_bounds.w - m_bounds.y) / m_precision + 1;

   std::vector<glm::vec2> shape;
   for (auto const& node : geometry.getNodes())
      shape.push_back(node.getPosition());

   // Determine nodes inside domain
   for (int row = 0; row < rowCount; ++row)
   {
      for (int column = 0; column < columnCount; ++column)
      {
         glm::vec2 point = { m_bounds.x + column * m_precision, m_bounds.y + row * m_precision };
         if (isPointInDomain(point, { point.x + 100.f, point.y }, shape))
            m_nodes.emplace(std::make_tuple(row, column), GridNode({ m_bounds.x + column * m_precision,
                                                                     m_bounds.y + row * m_precision }));
      }
   }
}

void Grid::findNeighboursAndBoundaries()
{
   for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
   {
      auto neighbours = findNeighbours(std::get<0>(it->first), std::get<1>(it->first));
      if (!neighbours)
         it->second.setBoundary();
      else
         it->second.setNeighbours(neighbours.value());
   }
}

void Grid::initBoundaryValues()
{
   for (auto& node : m_nodes)
   {
      if (node.second.isBoundary())
         node.second.setValue(1.0);
   }
}

std::optional<GridNode::Neighbours> Grid::findNeighbours(int x, int y)
{
   GridNode::Neighbours neighbours;

   // If at least one neighbour is missing -> it is boundary
   if (m_nodes.find(std::make_tuple(x - 1, y)) == m_nodes.end() ||
       m_nodes.find(std::make_tuple(x + 1, y)) == m_nodes.end() ||
       m_nodes.find(std::make_tuple(x, y + 1)) == m_nodes.end() ||
       m_nodes.find(std::make_tuple(x, y - 1)) == m_nodes.end())
      return std::nullopt;

   neighbours.left = &getNode(x - 1, y);
   neighbours.right = &getNode(x + 1, y);
   neighbours.up = &getNode(x, y + 1);
   neighbours.down = &getNode(x, y - 1);

   return neighbours;
}

bool Grid::isOnSegment(glm::vec2 const point, glm::vec2 const a, glm::vec2 const b) const
{
   // TODO Improve epsilon comparison
   return glm::abs(glm::distance(point, a) + glm::distance(point, b) - glm::distance(a, b)) < 0.00001f;
}

bool Grid::isPointInDomain(glm::vec2 const point, glm::vec2 const direction, std::vector<glm::vec2> const& shape) const
{
   int totalIntersections = 0;
   for (auto it = shape.begin(); it != shape.end() - 1; ++it)
   {
      if (doesSegmentsIntersect(point, direction, *it, *(it + 1)))
         totalIntersections++;
      if (isOnSegment(point, *it, *(it + 1)))
         return true;
   }
   // Last segment to close domain
   if (doesSegmentsIntersect(point, direction, *shape.begin(), *(shape.end() - 1)))
      totalIntersections++;
   if (isOnSegment(point, *shape.begin(), *(shape.end() - 1)))
      return true;

   // if odd, point is in shape
   return totalIntersections % 2;
}

bool Grid::doesSegmentsIntersect(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d) const
{
   return isCCW(a, c, d) != isCCW(b, c, d) && isCCW(a, b, c) != isCCW(a, b, d);
}

bool Grid::isCCW(glm::vec2 a, glm::vec2 b, glm::vec2 c) const
{
   return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

