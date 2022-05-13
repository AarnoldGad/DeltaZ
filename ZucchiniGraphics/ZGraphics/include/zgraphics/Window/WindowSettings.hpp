/**
 * WindowSettings.hpp
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
#ifndef ZG_WINDOWSETTINGS_HPP
#define ZG_WINDOWSETTINGS_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   struct WindowSettings
   {
      bool resisable = true;
      bool visible = true;
      bool decorated = true;
      bool focused = true;
      bool floating = false;
      bool maximised = false;
      bool centerCursor = true;
      bool focusOnShow = true;
      bool scaleToMonitor = false;
      int refreshRate = -1;
      bool doubleBuffering = true;
      bool autoIconify = true;
   };
}

#endif // ZG_WINDOWSETTINGS_HPP
