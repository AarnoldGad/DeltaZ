#include "zgpch.hpp"

#include "zgraphics/Renderer/Buffers/Buffer.hpp"

namespace zg
{
   namespace
   {
      GLenum TypeToGLenum(Buffer::Type type)
      {
         switch (type)
         {
            case Buffer::Type::Vertex:
               return GL_ARRAY_BUFFER;
            case Buffer::Type::Element:
               return GL_ELEMENT_ARRAY_BUFFER;
            default:
               return 0;
         }
      }

      GLenum UsageToGLenum(Buffer::Usage usage)
      {
         switch (usage)
         {
            case Buffer::Usage::Static:
               return GL_STATIC_DRAW;
            case Buffer::Usage::Dynamic:
               return GL_DYNAMIC_DRAW;
            default:
               return 0;
         }
      }
   }
   Buffer::Buffer(Type bufferType, Usage usage)
      : m_handle(0), m_type(bufferType), m_usage(usage)
   {
      glGenBuffers(1, &m_handle);
   }

   void Buffer::resize(size_t size)
   {
      bind();
      glBufferData(TypeToGLenum(m_type), size, nullptr, UsageToGLenum(m_usage));
   }

   void Buffer::setData(size_t size, void const* data)
   {
      bind();
      glBufferData(TypeToGLenum(m_type), size, data, UsageToGLenum(m_usage));
   }

   void Buffer::setSubData(ptrdiff_t offset, size_t size, void const* data)
   {
      bind();
      glBufferSubData(TypeToGLenum(m_type), offset, size, data);
   }

   void Buffer::bind() const noexcept
   {
      glBindBuffer(TypeToGLenum(m_type), m_handle);
   }

   void Buffer::unbind() const noexcept
   {
      glBindBuffer(TypeToGLenum(m_type), 0);
   }

   void* Buffer::map()
   {
      bind();
      return glMapBuffer(TypeToGLenum(m_type), GL_WRITE_ONLY);
   }

   void Buffer::unmap()
   {
      bind();
      glUnmapBuffer(TypeToGLenum(m_type));
   }

   Buffer::~Buffer()
   {
      glDeleteBuffers(1, &m_handle);
   }
}
