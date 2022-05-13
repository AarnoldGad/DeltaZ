/**
 * KeyboardImpl.hpp
 * 26 Feb 2022
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
#ifndef ZG_KEYBOARDIMPL_HPP
#define ZG_KEYBOARDIMPL_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Window/Window.hpp"
#include "zgraphics/Input/Keyboard.hpp"

#include <GLFW/glfw3.h>

namespace zg { namespace details
{
   class ZG_DETAIL KeyboardImpl
   {
   public:
      static std::string GetKeyName(Keyboard::Key key);
      static int GetKeyScancode(Keyboard::Key key);

      static bool IsKeyPressed(Keyboard::Key key);
      static uint32_t GetModifiers();

      static void SetFocusedWindow(Window* window);

   private:
      KeyboardImpl() = delete;

      static Window* s_window;
   };
}}

#endif // ZG_KEYBOARDIMPL_HPP
