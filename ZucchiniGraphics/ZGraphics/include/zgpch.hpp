/**
 * zepch.hpp
 * 4 Apr 2021
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
#ifndef ZG_PCH_HPP
#define ZG_PCH_HPP

#include "zgraphics/platform.hpp"

// Dependencies
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include <stb_image/stb_image.h>

// Streams
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

// Collections
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>

// Misc
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>
#include <thread>
#include <random>
#include <type_traits>
#include <chrono>

// C Legacy
#include <cstdint>
#include <cctype>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include <cstdio>

// Platform specific
#if defined(ZG_PLATFORM_WINDOWS)
   #include <Windows.h>

   #undef min
   #undef max
#elif defined(ZG_PLATFORM_LINUX) || defined(ZG_PLATFORM_APPLE)
   #include <sys/utsname.h>
   #include <dlfcn.h>
#endif

#endif // ZG_PCH_HPP
