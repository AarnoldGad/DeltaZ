#ifndef LEGEND_HPP
#define LEGEND_HPP

#include <zgraphics/zgraphics.hpp>

#include "dz/Graphics/NodeVertex.hpp"

class Legend : public zg::Mesh
{
public:
   size_t getVertexCount() const noexcept override;
   zg::Vertex const* getVertex(size_t index) const noexcept override;

   size_t getElementCount() const noexcept override;
   unsigned int const* getElements() const noexcept override;

   void setBounds(float height, float lower, float upper);

   Legend();

private:
   NodeVertex m_vertices[4];
};

#include "Legend.inl"

#endif // LEGEND_HPP

