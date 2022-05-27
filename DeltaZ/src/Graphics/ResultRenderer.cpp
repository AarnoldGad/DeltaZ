#include "dz/Graphics/ResultRenderer.hpp"

#include "dz/Graphics/NodeVertex.hpp"

#include <glad/glad.h>

namespace
{
   GLenum toGlPrimitive(Primitive primitive)
   {
      switch (primitive)
      {
         case Primitive::Points: return GL_POINTS;
         case Primitive::Lines: return GL_LINES;
         case Primitive::LineStrip: return GL_LINE_STRIP;
         case Primitive::Triangles: return GL_TRIANGLES;
         case Primitive::TriangleStrip: return GL_TRIANGLE_STRIP;
         case Primitive::TriangleFan: return GL_TRIANGLE_FAN;
         default: return GL_TRIANGLES;
      }
   }
}

void ResultRenderer::setLayout(zg::VertexLayout const& layout)
{
   m_vbo.bind();
   m_vao.setLayout(layout);
}

void ResultRenderer::setViewProjection(zg::ViewProjection const* viewProjection) noexcept
{
   m_viewProjection = viewProjection;
}

void ResultRenderer::submit(zg::Mesh const* mesh, glm::mat4 transform)
{
   m_objects.emplace(mesh, transform);
}

void ResultRenderer::render(zg::Shader* shader, bool isBoundary, Primitive primitive)
{
   if (shader)
   {
      shader->use();
      shader->setMatrix4("view", m_viewProjection->getViewMatrix());
      shader->setMatrix4("projection", m_viewProjection->getProjectionMatrix());

      shader->setBoolean("isBoundary", isBoundary);
   }

   for (auto& object : m_objects)
   {
      // TODO IT IS TOTALLY HARDCODED FOR NODEVERTEX !
      m_vao.bind();
      m_vbo.resize(object.first->getVertexCount()*sizeof(NodeVertex));
      m_ebo.setData(object.first->getElementCount() * sizeof(unsigned int),
                    object.first->getElements());

      {
         float* buffer = m_vbo.map<float>();
         for (size_t i = 0; i < object.first->getVertexCount(); ++i)
         {
            buffer[i*3 + 0] = reinterpret_cast<glm::vec2 const*>(object.first->getVertex(i)->getData(0))->x;
            buffer[i*3 + 1] = reinterpret_cast<glm::vec2 const*>(object.first->getVertex(i)->getData(0))->y;

            buffer[i*3 + 2] = *reinterpret_cast<float const*>(object.first->getVertex(i)->getData(1));
         }
         m_vbo.unmap();
      }

      shader->setMatrix4("model", object.second);

      glDrawElements(toGlPrimitive(primitive), object.first->getElementCount(), GL_UNSIGNED_INT, 0);
   }

   m_objects.clear();
}

