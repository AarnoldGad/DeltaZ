#include "zgpch.hpp"

#include "zgraphics/Renderer/Buffers/VertexBuffer.hpp"

namespace zg
{
   VertexBuffer::VertexBuffer()
      : Buffer(Buffer::Type::Vertex, Buffer::Usage::Static) {}
}
