/**
 * Transform.hpp
 * 25 Sep 2021
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
#ifndef ZE_TRANSFORM_HPP
#define ZE_TRANSFORM_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   class ZG_API Transform
   {
   public:
      glm::mat4 const& getTransformationMatrix() const;

      void setPosition(glm::vec3 pos) noexcept;
      void setOrigin(glm::vec3 origin) noexcept;
      void setScale(glm::vec3 scale) noexcept;
      void setRotation(ze::Angle angle, glm::vec3 axis);
      void setRotation(ze::Angle pitch, ze::Angle yaw, ze::Angle roll);

      void move(glm::vec3 offset) noexcept;
      void moveOrigin(glm::vec3 offset) noexcept;
      void scale(glm::vec3 factor) noexcept;
      void rotate(ze::Angle angle, glm::vec3 axis);
      void rotate(ze::Angle pitch, ze::Angle yaw, ze::Angle roll);

      glm::vec3 getPosition() const noexcept;
      glm::vec3 getOrigin() const noexcept;
      glm::vec3 getScale() const noexcept;
      glm::quat getRotation() const noexcept;

      Transform();

   private:
      mutable glm::mat4 m_transform;
      mutable bool m_dirty;

      glm::vec3 m_pos;
      glm::vec3 m_origin;
      glm::vec3 m_scale;
      glm::quat m_rotation;
   };
}

#endif /* ZE_TRANSFORM_HPP */
