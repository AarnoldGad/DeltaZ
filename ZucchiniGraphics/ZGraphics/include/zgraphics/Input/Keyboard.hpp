/**
 * Keyboard.hpp
 * 22 Jun 2021
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
#ifndef ZG_KEYBOARD_HPP
#define ZG_KEYBOARD_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   class ZG_API Keyboard
   {
   public:
      enum class Key : int
      {
         Unknown = -1,
         Space = 32,
         Apostrophe = 39,
         Comma = 44,
         Minus = 45,
         Period = 46,
         Slash = 47,
         Num0 = 48, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
         Semicolon = 59,
         Equal = 61,
         A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
         LeftBracket = 91,
         BackSlash = 92,
         RightBracket = 93,
         GraveAccent = 96,
         World1 = 161,
         World2 = 162,
         Escape = 256,
         Enter = 257,
         Tab = 258,
         Backspace = 259,
         Insert = 260,
         Delete = 261,
         Right = 262,
         Left = 263,
         Down = 264,
         Up = 265,
         PageUp = 266,
         PageDown = 267,
         Home = 268,
         End = 269,
         CapsLock = 280,
         ScrollLock = 281,
         NumLock = 282,
         PrintScreen = 283,
         Pause = 284,
         F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9,
         F10, F11, F12, F13, F14, F15, F16, F17, F18, F19,
         F20, F21, F22, F23, F24, F25,
         Keypad0 = 320, Keypad1, Keypad2, Keypad3, Keypad4,
         Keypad5, Keypad6, Keypad7, Keypad8, Keypad9,
         KeypadDecimal, KeypadDivide, KeypadMultiply, KeypadSubtract,
         KeypadAdd, KeypadEnter, KeypadEqual,
         LeftShift = 340, LeftControl, LeftAlt, LeftSuper, RightShift,
         RightControl, RightAlt, RightSuper, Menu
      };

      enum class Modifiers : uint32_t
      {
         Shift    = FLAG(0),
         Ctrl     = FLAG(1),
         Alt      = FLAG(2),
         Super    = FLAG(3),
         CapsLock = FLAG(4),
         NumLock  = FLAG(5)
      };

      static std::string GetKeyName(Key key);
      static int GetKeyScancode(Key key);

      static bool IsKeyPressed(Key key);
      static uint32_t GetModifiers();

   private:
      Keyboard() = delete;
   };
}

#endif // ZG_KEYBOARD_HPP
