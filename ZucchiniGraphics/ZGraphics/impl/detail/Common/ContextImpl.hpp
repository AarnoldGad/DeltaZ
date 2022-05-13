/**
 * ContextImpl.hpp
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
#ifndef ZG_CONTEXTIMPL_HPP
#define ZG_CONTEXTIMPL_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Window/Window.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace zg { namespace details
{
   class ZG_DETAIL ContextImpl
   {
   public:
      static void Initialise();
      static void LoadAPI();
      static void Terminate();

      static void LoadFreetype();
      static FT_Library GetFreetype();

      static void SetActiveContext(Window* window);
      static void PollEvents();

   private:
      ContextImpl() = delete;

      static void HandleGLFWError(int code, char const* description);

      static FT_Library s_freetype;
      static bool s_isInitialised;
      static bool s_isFreetypeLoaded;
   };
}}

#endif // ZG_CONTEXTIMPL_HPP

