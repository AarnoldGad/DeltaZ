/**
 * GLFWMouse.hpp
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
#ifndef ZG_MOUSEIMPL_HPP
#define ZG_MOUSEIMPL_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Input/Mouse.hpp"
#include "zgraphics/Window/Window.hpp"

#include <GLFW/glfw3.h>

namespace zg { namespace details
{
   class ZG_DETAIL MouseImpl
   {
   public:
      static std::string GetButtonName(Mouse::Button button);

      static bool IsButtonPressed(Mouse::Button button);
      static glm::ivec2 GetPosition();

      static void SetPosition(glm::ivec2 pos);
      static void SetCursorMode(Mouse::CursorMode mode);
      static void SetRawMouseMotion(bool raw);

      static void SetFocusedWindow(Window* window);

   private:
      MouseImpl() = delete;

      static Window* s_window;
   };
}}

#endif // ZG_MOUSEIMPL_HPP
