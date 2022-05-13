/**
 * FrameBufferSettings.hpp
 * 30 Jun 2021
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
#ifndef ZG_FRAMEBUFFERSETTINGS_HPP
#define ZG_FRAMEBUFFERSETTINGS_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   struct FrameBufferSettings
   {
      int redBits = 8;
      int greenBits = 8;
      int blueBits = 8;
      int alphaBits = 8;
      int depthBits = 24;
      int stencilBits = 8;
      int accumRedBits = 0;
      int accumGreenBits = 0;
      int accumBlueBits = 0;
      int accumAlphaBits = 0;
      bool srgbCapable = false;
      bool transparent = false;
   };
}

#endif // ZG_FRAMEBUFFERSETTINGS_HPP
