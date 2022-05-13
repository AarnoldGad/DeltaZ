#include "zgpch.hpp"

#include "zgraphics/Renderer/Transform.hpp"

namespace zg
{
   Transform::Transform()
      : m_transform(1.f), m_dirty(true), m_pos(0.f), m_origin(0.f), m_scale(1.f), m_rotation() {}

   glm::mat4 const& Transform::getTransformationMatrix() const
   {
      if (m_dirty)
      {
         m_transform = glm::mat4(1.f);

         m_transform = glm::scale(m_transform, m_scale);
         m_transform = glm::translate(m_transform, m_pos);
         m_transform = m_transform * glm::mat4_cast(m_rotation);
         m_transform = glm::translate(m_transform, -m_origin);

         m_dirty = false;
      }

      return m_transform;
   }

   void Transform::setPosition(glm::vec3 pos) noexcept
   {
      m_pos = pos;
      m_dirty = true;
   }

   void Transform::setOrigin(glm::vec3 origin) noexcept
   {
      m_origin = origin;
      m_dirty = true;
   }

   void Transform::setScale(glm::vec3 scale) noexcept
   {
      m_scale = scale;
      m_dirty = true;
   }

   void Transform::setRotation(ze::Angle angle, glm::vec3 axis)
   {
      m_rotation = glm::angleAxis(angle.asRadians(), axis);
      m_dirty = true;
   }

   void Transform::setRotation(ze::Angle pitch, ze::Angle yaw, ze::Angle roll)
   {
      m_rotation = glm::quat();
      m_rotation = glm::rotate(m_rotation, pitch.asRadians(), { 1.f, 0.f, 0.f });
      m_rotation = glm::rotate(m_rotation, yaw.asRadians(), { 0.f, 1.f, 0.f });
      m_rotation = glm::rotate(m_rotation, roll.asRadians(), { 0.f, 0.f, 1.f });
      m_dirty = true;
   }

   void Transform::move(glm::vec3 offset) noexcept
   {
      m_pos += offset;
      m_dirty = true;
   }

   void Transform::moveOrigin(glm::vec3 offset) noexcept
   {
      m_origin += offset;
      m_dirty = true;
   }

   void Transform::scale(glm::vec3 factor) noexcept
   {
      m_scale *= factor;
      m_dirty = true;
   }

   void Transform::rotate(ze::Angle angle, glm::vec3 axis)
   {
      m_rotation = glm::rotate(m_rotation, angle.asRadians(), axis);
      m_dirty = true;
   }

   void Transform::rotate(ze::Angle pitch, ze::Angle yaw, ze::Angle roll)
   {
      m_rotation = glm::rotate(m_rotation, pitch.asRadians(), { 1.f, 0.f, 0.f });
      m_rotation = glm::rotate(m_rotation, yaw.asRadians(), { 0.f, 1.f, 0.f });
      m_rotation = glm::rotate(m_rotation, roll.asRadians(), { 0.f, 0.f, 1.f });
      m_dirty = true;
   }
}
