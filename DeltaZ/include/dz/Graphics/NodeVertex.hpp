#ifndef NODEVERTEX_HPP
#define NODEVERTEX_HPP

#include "dz/Solver/Node.hpp"

#include <zgraphics/zgraphics.hpp>
#include <glad/glad.h>

class NodeVertex : public zg::Vertex
{
public:
   void const* getData(unsigned int location) const noexcept override;

   glm::vec2 getPosition() const noexcept;
   float getValue() const noexcept;

   void setPosition(glm::vec2 pos) noexcept;
   void setValue(float value) noexcept;

   explicit NodeVertex(glm::vec2 pos = {}, float value = 0.0);
   explicit NodeVertex(Node const& node);

private:
   glm::vec2 m_pos;
   float m_value;
};

#include "NodeVertex.inl"

#endif // NODEVERTEX_HPP
