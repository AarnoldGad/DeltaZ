/**
 * FrameBufferResisedEvent.hpp
 * 23 Jul 2021
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
#ifndef ZG_FRAMEBUFFERRESISEDEVENT_HPP
#define ZG_FRAMEBUFFERRESISEDEVENT_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Window/Event/WindowEvents.hpp"

namespace zg
{
   class ZG_API FrameBufferResisedEvent : public WindowEvent
   {
   public:
      glm::ivec2 getSize() const noexcept;

      std::string toString() const override;

      FrameBufferResisedEvent(Window* window, int width, int height);
   private:
      glm::ivec2 m_size;
   };
}

#include "FrameBufferResisedEvent.inl"

#endif /* ZG_FRAMEBUFFERRESISEDEVENT_HPP */
