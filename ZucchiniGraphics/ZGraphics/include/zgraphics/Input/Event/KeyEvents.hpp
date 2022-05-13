/**
 * KeyEvents.hpp
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
#ifndef ZG_KEYEVENTS_HPP
#define ZG_KEYEVENTS_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Window/Window.hpp"
#include "zgraphics/Input/Keyboard.hpp"

namespace zg
{
   class ZG_API KeyEvent : public ze::Event
   {
   public:
      enum class Action
      {
         Released = 0,
         Pressed,
         Repeated
      };

      Window* getWindow() noexcept;
      Keyboard::Key getKey() const noexcept;
      int getScancode() const noexcept;
      Action getAction() const noexcept;
      uint32_t getModifiers() const noexcept;

      explicit KeyEvent(Window* window, Keyboard::Key key, int scancode, Action action, uint32_t modifiers);

   protected:
      Window* m_window;
      Keyboard::Key m_key;
      int m_scancode;
      Action m_action;
      uint32_t m_modifiers;
   };

   class ZG_API KeyPressedEvent : public KeyEvent
   {
   public:
      std::string toString() const override;

      KeyPressedEvent(Window* window, Keyboard::Key key, int scancode, uint32_t modifiers);
   };

   class ZG_API KeyReleasedEvent : public KeyEvent
   {
   public:
      std::string toString() const override;

      KeyReleasedEvent(Window* window, Keyboard::Key key, int scancode, uint32_t modifiers);
   };

   class ZG_API KeyRepeatedEvent : public KeyEvent
   {
   public:
      std::string toString() const override;

      KeyRepeatedEvent(Window* window, Keyboard::Key key, int scancode, uint32_t modifiers);
   };
}

#include "KeyEvents.inl"

#endif // ZG_KEYEVENTS_HPP
