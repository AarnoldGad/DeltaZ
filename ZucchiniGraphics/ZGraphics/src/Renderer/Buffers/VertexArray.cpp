#include "zgpch.hpp"

#include "zgraphics/Renderer/Buffers/VertexArray.hpp"

namespace zg
{
   namespace
   {
      static GLenum TypeToGLenum(VertexAttribute::Type type) noexcept
      {
         switch (type)
         {
            case VertexAttribute::Type::Float: return GL_FLOAT;
            case VertexAttribute::Type::Vec2:  return GL_FLOAT;
            case VertexAttribute::Type::Vec3:  return GL_FLOAT;
            case VertexAttribute::Type::Vec4:  return GL_FLOAT;
            case VertexAttribute::Type::Int:   return GL_INT;
            case VertexAttribute::Type::IVec2: return GL_INT;
            case VertexAttribute::Type::IVec3: return GL_INT;
            case VertexAttribute::Type::IVec4: return GL_INT;
            case VertexAttribute::Type::Mat3:  return GL_FLOAT;
            case VertexAttribute::Type::Mat4:  return GL_FLOAT;
            case VertexAttribute::Type::Bool:  return GL_INT;
         }

         ZE_ASSERT(false, "Unrecognised attribute type !");
         return 0;
      }

      static int GetTypeComponentCount(VertexAttribute::Type type) noexcept
      {
         switch (type)
         {
            case VertexAttribute::Type::Float: return 1;
            case VertexAttribute::Type::Vec2:  return 2;
            case VertexAttribute::Type::Vec3:  return 3;
            case VertexAttribute::Type::Vec4:  return 4;
            case VertexAttribute::Type::Int:   return 1;
            case VertexAttribute::Type::IVec2: return 2;
            case VertexAttribute::Type::IVec3: return 3;
            case VertexAttribute::Type::IVec4: return 4;
            case VertexAttribute::Type::Mat3:  return 9;
            case VertexAttribute::Type::Mat4:  return 16;
            case VertexAttribute::Type::Bool:  return 1;
         }

         ZE_ASSERT(false, "Unrecognised attribute type !");
         return 0;
      }
   }

   VertexArray::VertexArray()
      : m_vao(0)
   {
      glGenVertexArrays(1, &m_vao);
   }

   void VertexArray::bind()
   {
      glBindVertexArray(m_vao);
   }

   void VertexArray::unbind()
   {
      glBindVertexArray(0);
   }

   void VertexArray::setLayout(VertexLayout const& layout)
   {
      bind();

      for (auto const& attribute : layout)
      {
         glVertexAttribPointer(attribute.index, GetTypeComponentCount(attribute.type),
                               TypeToGLenum(attribute.type), attribute.normalised ? GL_TRUE : GL_FALSE,
                               layout.getStride(), reinterpret_cast<void*>(attribute.offset));
         glEnableVertexAttribArray(attribute.index);
      }

      m_layout = layout;
   }

   VertexArray::~VertexArray()
   {
      glDeleteVertexArrays(1, &m_vao);
   }
}

