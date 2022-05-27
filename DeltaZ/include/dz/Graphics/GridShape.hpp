#ifndef GRIDSHAPE_HPP
#define GRIDSHAPE_HPP

#include <zgraphics/zgraphics.hpp>

#include "dz/Solver/Grid.hpp"
#include "dz/Graphics/NodeVertex.hpp"

class GridShape : public zg::Mesh
{
public:
   size_t getVertexCount() const noexcept;
   zg::Vertex const* getVertex(size_t index) const noexcept;

   size_t getElementCount() const noexcept;
   unsigned int const* getElements() const noexcept;

   void setGrid(Grid const& grid);

   GridShape() = default;

private:
   std::vector<NodeVertex> m_vertices;
   std::vector<unsigned int> m_elements;
};

#include "GridShape.inl"

#endif // GRIDSHAPE_HPP

