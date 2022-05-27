#include "dz/Graphics/GeometryShape.hpp"

void GeometryShape::setGeometry(Geometry const& geometry)
{
   m_elements.reserve(geometry.getNodes().size() * 2);
   m_maxValue = 0.f;
   m_minValue = 0.f;

   size_t i = 0;
   for (auto it = geometry.getNodes().begin(); it != geometry.getNodes().end(); ++it)
   {
      Node const& node = *it;
      m_vertices.push_back(NodeVertex(node));

      m_elements.push_back(i);
      if (it < geometry.getNodes().end() - 1)
         m_elements.push_back(++i);
      else
         m_elements.push_back(0);

      m_minValue = glm::min(m_minValue, node.getValue());
      m_maxValue = glm::max(m_maxValue, node.getValue());
   }
}

