/**
 * Camera.hpp
 * 26 Oct 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZG_CAMERA_HPP
#define ZG_CAMERA_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Renderer/ViewProjection.hpp"

namespace zg
{
   class ZG_API Camera : public ViewProjection
   {
   public:
      glm::mat4 const& getViewMatrix() const override;
      glm::mat4 const& getProjectionMatrix() const override;

      void setFront(glm::vec3 front) noexcept;
      void setUp(glm::vec3 up) noexcept;
      void setFieldOfView(ze::Angle fov) noexcept;
      void setAspectRatio(float ratio) noexcept;
      void setPosition(glm::vec3 pos) noexcept;

      void move(glm::vec3 offset) noexcept;

      glm::vec3 getFront() const noexcept;
      glm::vec3 getUp() const noexcept;
      ze::Angle getFieldOfView() const noexcept;
      float getAspectRatio() const noexcept;
      glm::vec3 getPosition() const noexcept;

      explicit Camera(ze::Angle fov, float ratio = 1.f, glm::vec3 pos = {}, glm::vec3 front = { 0.f, 0.f, -1.f }, glm::vec3 up = { 0.f, 1.f, 0.f });

   protected:
      mutable glm::mat4 m_viewCache;
      mutable glm::mat4 m_projectionCache;
      mutable bool m_viewDirty;
      mutable bool m_projectionDirty;

      glm::vec3 m_pos;
      glm::vec3 m_front;
      glm::vec3 m_up;

      ze::Angle m_fov;
      float m_ratio;
   };
}

#include "Camera.inl"

#endif // ZG_CAMERA_HPP
