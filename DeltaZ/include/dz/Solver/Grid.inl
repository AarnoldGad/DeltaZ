inline float Grid::getPrecision() const noexcept
{
   return m_precision;
}

inline glm::vec4 Grid::getBounds() const noexcept
{
   return m_bounds;
}

inline Node& Grid::getNode(int const x, int const y)
{
   return m_nodes.at(std::tie(x, y));
}

inline Node const& Grid::getNode(int const x, int const y) const
{
   return m_nodes.at(std::tie(x, y));
}

inline std::map<std::tuple<int, int>, Node>& Grid::getNodes() noexcept
{
   return m_nodes;
}

inline std::map<std::tuple<int, int>, Node> const& Grid::getNodes() const noexcept
{
   return m_nodes;
}

inline bool Grid::isPointInShape(glm::vec2 const point, std::vector<Node> const& closedShape) const
{
   // FIXME Point detected as in the shape because colinear
   // with one same end of multiple different segments
   glm::vec2 direction = point + glm::vec2(100.f, 0.f);
   int totalIntersections = 0;

   for (auto node = closedShape.begin(); node != closedShape.end() - 1; ++node)
   {
      if (doesSegmentsIntersect(point, direction, node->getPosition(), (node + 1)->getPosition()))
         totalIntersections++;
      if (isOnSegment(point, node->getPosition(), (node + 1)->getPosition()))
         return true;
   }

   // if odd, point is in shape
   return totalIntersections % 2;
}

inline float Grid::distanceFromSegment(glm::vec2 const point, glm::vec2 const segmentStart,
                                                       glm::vec2 const segmentEnd) const
{
   float segmentLength = glm::distance(segmentStart, segmentEnd);
   float pointDotEnd = glm::dot(point - segmentStart, segmentEnd - segmentStart);
   float ratio = pointDotEnd / (segmentLength * segmentLength);

   return ratio < 0.f ? glm::distance(point, segmentStart) :
         (ratio > 1.f ? glm::distance(point, segmentEnd) :
          glm::distance(point, segmentStart + ratio * (segmentEnd - segmentStart)));
}

inline bool Grid::isOnSegment(glm::vec2 const point, glm::vec2 const segmentStart,
                                              glm::vec2 const segmentEnd) const
{
   // TODO Improve epsilon comparison
   return distanceFromSegment(point, segmentStart, segmentEnd) < (m_precision / 2.f + 0.00001f);
}

inline bool Grid::doesSegmentsIntersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2) const
{
   if (findOrientation(a1, a2, b1) == Orientation::Colinear && findOrientation(a1, a2, b2) == Orientation::Colinear)
      return false;
   return findOrientation(a1, b1, b2) != findOrientation(a2, b1, b2)
       && findOrientation(a1, a2, b1) != findOrientation(a1, a2, b2);
   // TODO Better handle colinearity
}

inline Grid::Orientation Grid::findOrientation(glm::vec2 a, glm::vec2 b, glm::vec2 c) const
{
   float idk = (b.y - a.y) * (c.x - a.x) - (c.y - a.y) * (b.x - a.x);
   // TODO Better epsilon comparison ?
   if (glm::abs(idk) < 0.00001f)
      return Orientation::Colinear;
   return idk > 0.f ? Orientation::Clockwise : Orientation::CounterClockwise;
}

