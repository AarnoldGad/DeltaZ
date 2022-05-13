#include "zgpch.hpp"

#include "zgraphics/Camera/Camera.hpp"

namespace zg
{
   Camera::Camera(ze::Angle const fov, float const ratio,
                  glm::vec3 const pos, glm::vec3 const front, glm::vec3 const up)
      : m_viewCache{}, m_projectionCache{}, m_viewDirty(true), m_projectionDirty(true),
        m_pos(pos), m_front(front), m_up(up), m_fov(fov), m_ratio(ratio) {}

   glm::mat4 const& Camera::getViewMatrix() const
   {
      if (m_viewDirty)
      {
         m_viewCache = glm::lookAt(m_pos, m_pos + m_front, m_up);

         m_viewDirty = false;
      }

      return m_viewCache;
   }

   glm::mat4 const& Camera::getProjectionMatrix() const
   {
      if (m_projectionDirty)
      {
         m_projectionCache = glm::perspective(m_fov.asRadians(), m_ratio, 0.1f, 100.f);

         m_projectionDirty = false;
      }

      return m_projectionCache;
   }

   void Camera::setFront(glm::vec3 const front) noexcept
   {
      m_front = front;
      m_viewDirty = true;
   }

   void Camera::setUp(glm::vec3 const up) noexcept
   {
      m_up = up;
      m_viewDirty = true;
   }

   void Camera::setFieldOfView(ze::Angle const fov) noexcept
   {
      m_fov = fov;
      m_projectionDirty = true;
   }

   void Camera::setAspectRatio(float const ratio) noexcept
   {
      m_ratio = ratio;
      m_projectionDirty = true;
   }

   void Camera::setPosition(glm::vec3 const pos) noexcept
   {
      m_pos = pos;
      m_viewDirty = true;
   }

   void Camera::move(glm::vec3 const offset) noexcept
   {
      m_pos += offset;
      m_viewDirty = true;
   }
}
