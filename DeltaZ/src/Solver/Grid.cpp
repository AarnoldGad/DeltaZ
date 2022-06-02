#include "dz/Solver/Grid.hpp"

#include <algorithm>
#include <array>
#include <glm/gtc/epsilon.hpp>

Grid::Grid()
   : m_precision{} {}

void Grid::configureGridFrom(Geometry const& geometry)
{
   m_precision = geometry.getPrecision();
   
   std::vector<std::tuple<Node, Node> > segments;
   for (auto const& armature : geometry.getArmatures())
   {
      for (auto nodeIt = armature.begin(); nodeIt != armature.end() - 1; ++nodeIt)
         segments.push_back(std::make_tuple(*nodeIt, *(nodeIt + 1)));
   }

   setGridBounds(geometry);
   generateGrid(segments, geometry.getMode());
   initNeighbours();
   initBoundaries(segments);
}

void Grid::setGridBounds(Geometry const& geometry)
{
   m_bounds = { 0.f, 0.f, 0.f, 0.f };
   for (auto const& armature : geometry.getArmatures())
      for (auto const& node : armature)
      {
         if (node.getPosition().x < m_bounds.x) m_bounds.x = node.getPosition().x;
         if (node.getPosition().y < m_bounds.y) m_bounds.y = node.getPosition().y;
         if (node.getPosition().x > m_bounds.z) m_bounds.z = node.getPosition().x;
         if (node.getPosition().y > m_bounds.w) m_bounds.w = node.getPosition().y;
      }

   if (geometry.getMode() == Mode::Expanded)
   {
      float expansionFactor = 0.3;
      float widthSupp = (m_bounds.x - m_bounds.z) * expansionFactor;
      float heightSupp = (m_bounds.y - m_bounds.w) * expansionFactor;
      m_bounds.x += widthSupp;
      m_bounds.y += heightSupp;
      m_bounds.z -= widthSupp;
      m_bounds.w -= heightSupp;
   }
}

void Grid::generateGrid(std::vector<std::tuple<Node, Node> > const& segments, Mode mode)
{
   int columnCount = (m_bounds.z - m_bounds.x) / m_precision + 1;
   int rowCount = (m_bounds.w - m_bounds.y) / m_precision + 1;

   // Determine nodes inside domain
   for (int row = 0; row < rowCount; ++row)
   {
      for (int column = 0; column < columnCount; ++column)
      {
         glm::vec2 point = { m_bounds.x + column * m_precision, m_bounds.y + row * m_precision };
         if (mode == Mode::Closed)
         {
            if (isPointInShape(point, segments))
               m_nodes.emplace(std::make_tuple(row, column), Node({ m_bounds.x + column * m_precision,
                                                                    m_bounds.y + row * m_precision }));
         }
         else if (mode == Mode::Expanded)
         {
            m_nodes.emplace(std::make_tuple(row, column), Node({ m_bounds.x + column * m_precision,
                                                                 m_bounds.y + row * m_precision }));
         }
      }
   }
}

void Grid::initNeighbours()
{
   for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
      it->second.setNeighbours(findNeighbours(std::get<0>(it->first), std::get<1>(it->first)));
}

void Grid::initBoundaries(std::vector<std::tuple<Node, Node> > const& segments)
{
   for (auto& element : m_nodes)
   {
      Node& node = element.second;
      std::tuple<Node, Node> closestSegment{ *(segments.begin()) };
      float smallerDistance = distanceFromSegment(node.getPosition(),
                                                  std::get<0>(closestSegment).getPosition(),
                                                  std::get<1>(closestSegment).getPosition());

      for (auto const& segment : segments)
      {
         float distance = distanceFromSegment(node.getPosition(), std::get<0>(segment).getPosition(),
                                                                  std::get<1>(segment).getPosition());
         if (distance < smallerDistance)
         {
            smallerDistance = distance;
            closestSegment= segment;
         }
      }

      if (smallerDistance < (m_precision - 0.00001f))
      {
         node.setBoundary();
         node.setValue(interpolate(node, closestSegment));
      }
   }
}

float Grid::interpolate(Node const& point, std::tuple<Node, Node> const& segment) const
{
   Node const& segmentStart = std::get<0>(segment);
   Node const& segmentEnd = std::get<1>(segment);
   float totalLength = glm::distance(point.getPosition(), segmentStart.getPosition())
                     + glm::distance(point.getPosition(), segmentEnd.getPosition());
   float ratio = glm::distance(point.getPosition(), segmentStart.getPosition()) / totalLength;
   return segmentStart.getValue() * (1.f - ratio) +  segmentEnd.getValue() * ratio;
}

Node::Neighbours Grid::findNeighbours(int x, int y)
{
   Node::Neighbours neighbours;

   decltype(m_nodes)::const_iterator foundNode;
   if (foundNode = m_nodes.find(std::make_tuple(x - 1, y)), foundNode != m_nodes.end())
      neighbours.left = &foundNode->second;
   if (foundNode = m_nodes.find(std::make_tuple(x + 1, y)), foundNode != m_nodes.end())
      neighbours.right = &foundNode->second;
   if (foundNode = m_nodes.find(std::make_tuple(x, y - 1)), foundNode != m_nodes.end())
      neighbours.down = &foundNode->second;
   if (foundNode = m_nodes.find(std::make_tuple(x, y + 1)), foundNode != m_nodes.end())
      neighbours.up = &foundNode->second;

   if (foundNode = m_nodes.find(std::make_tuple(x - 1, y + 1)), foundNode != m_nodes.end())
      neighbours.leftUp = &foundNode->second;
   if (foundNode = m_nodes.find(std::make_tuple(x + 1, y + 1)), foundNode != m_nodes.end())
      neighbours.rightUp = &foundNode->second;
   if (foundNode = m_nodes.find(std::make_tuple(x - 1, y - 1)), foundNode != m_nodes.end())
      neighbours.leftDown = &foundNode->second;
   if (foundNode = m_nodes.find(std::make_tuple(x + 1, y - 1)), foundNode != m_nodes.end())
      neighbours.rightDown = &foundNode->second;

   return neighbours;
}

