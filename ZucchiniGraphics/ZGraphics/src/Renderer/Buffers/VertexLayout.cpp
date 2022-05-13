#include "zgraphics/Renderer/Buffers/VertexLayout.hpp"

namespace zg
{
   VertexLayout::VertexLayout()
      : m_stride{} {}

   void VertexLayout::add(VertexAttribute::Type type, std::string const& name, bool normalised)
   {
      add(VertexAttribute(type, name, normalised));
   }

   void VertexLayout::add(VertexAttribute&& attribute)
   {
      attribute.offset = m_stride;
      attribute.index = m_attributes.size();
      m_stride += attribute.byteSize;
      m_attributes.push_back(std::move(attribute));
   }
}
