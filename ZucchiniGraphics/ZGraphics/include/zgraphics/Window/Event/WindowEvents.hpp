/**
 * WindowEvents.hpp
 * 28 Jun 2021
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
#ifndef ZG_WINDOWEVENTS_HPP
#define ZG_WINDOWEVENTS_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   class Window;

   class ZG_API WindowEvent : public ze::Event
   {
   public:
      Window* getWindow() noexcept;
      Window const* getWindow() const noexcept;

      explicit WindowEvent(Window* window);

   protected:
      Window* m_window;
   };

   class ZG_API WindowClosedEvent : public WindowEvent
   {
   public:
      WindowClosedEvent(Window* window);

      std::string toString() const;
   };

   class ZG_API WindowFocusedEvent : public WindowEvent
   {
   public:
      bool isFocused() const noexcept;

      std::string toString() const override;

      WindowFocusedEvent(Window* window, bool focused);
   private:
      bool const m_focused;
   };

   class ZG_API WindowIconifiedEvent : public WindowEvent
   {
   public:
      bool isIconified() const noexcept;

      std::string toString() const override;

      WindowIconifiedEvent(Window* window, int iconified);

   private:
      bool m_iconified;
   };

   class ZG_API WindowMaximisedEvent : public WindowEvent
   {
   public:
      bool isMaximised() const noexcept;

      std::string toString() const override;

      WindowMaximisedEvent(Window* window, int maximised);

   private:
      bool m_maximised;
   };

   class ZG_API WindowMovedEvent : public WindowEvent
   {
   public:
      glm::ivec2 getPosition() const noexcept;
      glm::ivec2 getOffset() const noexcept;

      std::string toString() const override;

      WindowMovedEvent(Window* window, glm::ivec2 newPos, glm::ivec2 oldPos);
   
   private:
      glm::ivec2 const m_pos;
      glm::ivec2 const m_offset;
   };

   class ZG_API WindowRefreshedEvent : public WindowEvent
   {
   public:
      std::string toString() const override;

      WindowRefreshedEvent(Window* window);
   };

   class ZG_API WindowResisedEvent : public WindowEvent
   {
   public:
      glm::ivec2 getSize() const noexcept;
      glm::ivec2 getOffset() const noexcept;

      std::string toString() const override;

      WindowResisedEvent(Window* window, glm::ivec2 newSize, glm::ivec2 oldSize);
   private:
      glm::ivec2 const m_size;
      glm::ivec2 const m_offset;
   };

   class ZG_API WindowScaledEvent : public WindowEvent
   {
   public:
      glm::vec2 getScale() const noexcept;

      std::string toString() const override;

      WindowScaledEvent(Window* window, float xscale, float yscale);

   private:
      glm::vec2 m_scale;
   };
}

#include "WindowEvents.inl"

#endif // ZG_WINDOWEVENTS_HPP
