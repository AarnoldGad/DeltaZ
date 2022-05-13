/**
 * MouseEvents.hpp
 * 6 May 2022
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
#ifndef ZG_MOUSEEVENT_HPP
#define ZG_MOUSEEVENT_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Window/Window.hpp"
#include "zgraphics/Input/Mouse.hpp"

namespace zg
{
   class ZG_API MouseEvent : public ze::Event
   {
   public:
      Window* getWindow() noexcept;
      glm::ivec2 getPosition() const noexcept;

      MouseEvent(Window* window, glm::ivec2 pos);

   protected:
      Window* m_window;
      glm::ivec2 m_pos;
   };

   class ZG_API MouseEnteredEvent : public MouseEvent
   {
   public:
      bool hasEntered() const noexcept;
      bool hasLeaved() const noexcept;

      std::string toString() const override;

      MouseEnteredEvent(Window* window, glm::ivec2 pos, bool entered);

   private:
      bool m_entered;
   };

   class ZG_API MouseMovedEvent : public MouseEvent
   {
   public:
      std::string toString() const override;

      MouseMovedEvent(Window* window, glm::ivec2 pos);
   };

   class ZG_API MouseScrolledEvent : public MouseEvent
   {
   public:
      double getHorizontalOffset() const noexcept;
      double getVerticalOffset() const noexcept;

      std::string toString() const override;

      MouseScrolledEvent(Window* window, glm::ivec2 pos, double xoffset, double yoffset);

   private:
      double m_xoffset;
      double m_yoffset;
   };

   class ZG_API MouseDroppedEvent : public MouseEvent
   {
   public:
      std::vector<std::filesystem::path> const& getPaths() const noexcept;
      std::filesystem::path getPath(size_t index) const;
      size_t getPathCount() const noexcept;

      std::string toString() const override;

      explicit MouseDroppedEvent(Window* window, glm::ivec2 pos, size_t count, char const* paths[]);

   private:
      std::vector<std::filesystem::path> m_paths;
   };

   class ZG_API MouseButtonEvent : public MouseEvent
   {
   public:
      enum class Action
      {
         Released = 0,
         Pressed
      };

      Mouse::Button getButton() const noexcept;
      Action getAction() const noexcept;
      uint32_t getModifiers() const noexcept;

      MouseButtonEvent(Window* window, glm::ivec2 pos, Mouse::Button button, Action action, uint32_t modifiers);

   protected:
      Mouse::Button m_button;
      Action m_action;
      uint32_t m_modifiers;
   };

   class ZG_API MouseButtonPressedEvent : public MouseButtonEvent
   {
   public:
      std::string toString() const override;

      MouseButtonPressedEvent(Window* window, glm::ivec2 pos, Mouse::Button button, uint32_t modifiers);
   };

   class ZG_API MouseButtonReleasedEvent : public MouseButtonEvent
   {
   public:
      std::string toString() const override;

      MouseButtonReleasedEvent(Window* window, glm::ivec2 pos, Mouse::Button button, uint32_t modifiers);
   };
}

#include "MouseEvents.inl"

#endif // ZG_MOUSEEVENT_HPP
