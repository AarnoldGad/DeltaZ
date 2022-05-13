#include "zgpch.hpp"

#include "zgraphics/Renderer/Buffers/IndexBuffer.hpp"

namespace zg
{
   static_assert(sizeof(unsigned char ) == sizeof(GLubyte ));
   static_assert(sizeof(unsigned short) == sizeof(GLushort));
   static_assert(sizeof(unsigned int  ) == sizeof(GLuint  ));

   IndexBuffer::IndexBuffer(DataType type)
      : Buffer(Buffer::Type::Element, Buffer::Usage::Static), m_dataType(type) {}
}
