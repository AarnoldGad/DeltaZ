#include "zgpch.hpp"

#include "zgraphics/Renderer/DefaultRenderer.hpp"

namespace zg
{
   void DefaultRenderer::setLayout(VertexLayout const& layout)
   {
      m_vbo.bind(); // Need to bind vbo to change layout
      m_vao.setLayout(layout);
   }

   void DefaultRenderer::setViewProjection(ViewProjection const* viewProjection) noexcept
   {
      m_viewProjection = viewProjection;
   }

   void DefaultRenderer::submit(TexturedMesh const& object, glm::mat4 transform)
   {
      m_objects.emplace(&object, transform);
   }

   void DefaultRenderer::render(Shader& shader)
   {
      shader.use();

      shader.setMatrix4("view", m_viewProjection->getViewMatrix());
      shader.setMatrix4("projection", m_viewProjection->getProjectionMatrix());

      for (auto& object : m_objects)
      {
         for (size_t i = 0; i < object.first->getTextureCount(); ++i)
         {
            glActiveTexture(GL_TEXTURE0 + i);
            object.first->getTexture(i)->bind();
            shader.setInteger("tex" + std::to_string(i), (int) i);
         }

         m_vao.bind();

         m_vbo.resize(object.first->getVertexCount()*8*sizeof(float));

         m_ebo.setData(sizeof(unsigned int) * object.first->getElementCount(), object.first->getElements());

         {
            float* buffer = m_vbo.map<float>();
            for (size_t i = 0; i < object.first->getVertexCount(); ++i)
            {
               buffer[i*8 + 0] = reinterpret_cast<glm::vec2 const*>(object.first->getVertex(i)->getData(0))->x;
               buffer[i*8 + 1] = reinterpret_cast<glm::vec2 const*>(object.first->getVertex(i)->getData(0))->y;

               buffer[i*8 + 2] = reinterpret_cast<glm::vec4 const*>(object.first->getVertex(i)->getData(1))->x;
               buffer[i*8 + 3] = reinterpret_cast<glm::vec4 const*>(object.first->getVertex(i)->getData(1))->y;
               buffer[i*8 + 4] = reinterpret_cast<glm::vec4 const*>(object.first->getVertex(i)->getData(1))->z;
               buffer[i*8 + 5] = reinterpret_cast<glm::vec4 const*>(object.first->getVertex(i)->getData(1))->w;

               buffer[i*8 + 6] = reinterpret_cast<glm::vec2 const*>(object.first->getVertex(i)->getData(2))->x;
               buffer[i*8 + 7] = reinterpret_cast<glm::vec2 const*>(object.first->getVertex(i)->getData(2))->y;
            }
            m_vbo.unmap();
         }

         shader.setMatrix4("model", object.second);

         glDrawElements(GL_TRIANGLES, object.first->getElementCount(), GL_UNSIGNED_INT, 0);
      }

      m_objects.clear();
   }
}
