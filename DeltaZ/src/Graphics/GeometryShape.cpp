#include "dz/Graphics/GeometryShape.hpp"

void GeometryShape::setGeometry(Geometry const& geometry)
{
   m_maxValue = 0.f;
   m_minValue = 0.f;
   size_t i = 0;
   
   for (auto const& armature : geometry.getArmatures())
   {
      for (auto nodeIt = armature.begin(); nodeIt != armature.end(); ++nodeIt)
      {
         Node const& node = *nodeIt;
         m_vertices.push_back(NodeVertex(node));

         if (nodeIt < armature.end() - 1)
         {
            m_elements.push_back(i);
            m_elements.push_back(++i);
         }

         m_minValue = glm::min(m_minValue, node.getValue());
         m_maxValue = glm::max(m_maxValue, node.getValue());
      }
      ++i;
   }
}

