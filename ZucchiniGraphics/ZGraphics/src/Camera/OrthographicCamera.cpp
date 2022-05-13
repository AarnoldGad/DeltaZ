#include "zgpch.hpp"

#include "zgraphics/Camera/OrthographicCamera.hpp"

namespace zg
{
   OrthographicCamera::OrthographicCamera(glm::vec2 const size, glm::vec2 const centre)
      : m_viewCache{}, m_projectionCache{}, m_viewDirty(true), m_projDirty(true),
        m_size(size), m_centre(centre) {}

   glm::mat4 const& OrthographicCamera::getViewMatrix() const
   {
      if (m_viewDirty)
      {
         m_viewCache = glm::mat4(1.f);

         m_viewCache = glm::translate(m_viewCache, glm::vec3(-m_centre + m_size / 2.f, 0.f));
         m_viewCache = glm::rotate(m_viewCache, m_rotation.asRadians(), { 0.f, 0.f, 1.f });

         m_viewDirty = false;
      }

      return m_viewCache;
   }

   glm::mat4 const& OrthographicCamera::getProjectionMatrix() const
   {
      if (m_projDirty)
      {
         m_projectionCache = glm::ortho(0.f, m_size.x, m_size.y, 0.f, 0.f, 100.f);

         m_projDirty = false;
      }

      return m_projectionCache;
   }

   void OrthographicCamera::setSize(glm::vec2 const size) noexcept
   {
      m_size = size;
      m_projDirty = true;
   }

   void OrthographicCamera::setCentre(glm::vec2 const pos) noexcept
   {
      m_centre = pos;
      m_viewDirty = true;
   }

   void OrthographicCamera::setRotation(ze::Angle const angle) noexcept
   {
      m_rotation = angle;
      m_viewDirty = true;
   }

   void OrthographicCamera::move(glm::vec2 const offset) noexcept
   {
      m_centre += offset;
      m_viewDirty = true;
   }

   void OrthographicCamera::rotate(ze::Angle const angle) noexcept
   {
      m_rotation += angle;
      m_viewDirty = true;
   }
}
