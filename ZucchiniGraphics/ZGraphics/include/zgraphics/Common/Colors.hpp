/**
 * Colors.hpp
 * 1 Jul 2021
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
#ifndef ZG_COLORS_HPP
#define ZG_COLORS_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   namespace Colors
   {
      glm::vec4 constexpr Red =   { 1.f, 0.f, 0.f, 1.f };
      glm::vec4 constexpr Green = { 0.f, 1.f, 0.f, 1.f };
      glm::vec4 constexpr Blue =  { 0.f, 0.f, 1.f, 1.f };

      glm::vec4 constexpr Magenta = { 1.f, 0.f, 1.f, 1.f };
      glm::vec4 constexpr Cyan =    { 0.f, 1.f, 1.f, 1.f };
      glm::vec4 constexpr Yellow =  { 1.f, 1.f, 0.f, 1.f };

      glm::vec4 constexpr White = { 1.f , 1.f , 1.f , 1.f };
      glm::vec4 constexpr Gray =  { 0.5f, 0.5f, 0.5f, 1.f };
      glm::vec4 constexpr Black = { 0.f , 0.f , 0.f , 1.f };

      glm::vec4 constexpr Orange = { 1.f  , 0.6f , 0.f  , 1.f };
      glm::vec4 constexpr Brown =  { 0.95f, 0.55f, 0.1f , 1.f };
      glm::vec4 constexpr Beige =  { 0.98f, 0.98f, 0.88f, 1.f };
      glm::vec4 constexpr Silver = { 0.75f, 0.75f, 0.75f, 1.f };
      glm::vec4 constexpr Gold =   { 1.f  , 0.85f, 0.f  , 1.f };
   }
}

#endif // ZG_COLORS_HPP
