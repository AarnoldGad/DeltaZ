#ifndef GEOMETRYSHAPE_HPP
#define GEOMETRYSHAPE_HPP

#include <zgraphics/zgraphics.hpp>

#include "dz/Solver/Geometry.hpp"
#include "dz/Graphics/NodeVertex.hpp"

class GeometryShape : public zg::Mesh
{
public:
   size_t getVertexCount() const noexcept;
   zg::Vertex const* getVertex(size_t index) const noexcept;
   
   size_t getElementCount() const noexcept;
   unsigned int const* getElements() const noexcept;

   float getMinValue() const noexcept;
   float getMaxValue() const noexcept;
   
   void setGeometry(Geometry const& grid);

   GeometryShape() = default;

private:
   float m_minValue;
   float m_maxValue;
   std::vector<NodeVertex> m_vertices;
   std::vector<unsigned int> m_elements;
};

#include "GeometryShape.inl"

#endif // GEOMETRYSHAPE_HPP

