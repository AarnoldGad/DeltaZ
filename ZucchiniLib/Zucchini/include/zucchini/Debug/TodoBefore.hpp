/**
 * TodoBefore.hpp
 * 7 May 2022
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2022 Gaétan Jalin
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

// Inspired by https://www.fluentcpp.com/2019/01/01/todo_before-clean-codebase-2019/

#include "zucchini/defines.hpp"

#include <string_view>

inline constexpr int currentMonth()
{
   // __DATE__ Format "Mmm dd yyyy"
   constexpr std::string_view date{__DATE__};
   constexpr std::string_view month{date.substr(0, 3)};

   using std::operator""sv;
   if ("Jan"sv.compare(month) == 0) return 1;
   if ("Feb"sv.compare(month) == 0) return 2;
   if ("Mar"sv.compare(month) == 0) return 3;
   if ("Apr"sv.compare(month) == 0) return 4;
   if ("May"sv.compare(month) == 0) return 5;
   if ("Jun"sv.compare(month) == 0) return 6;
   if ("Jul"sv.compare(month) == 0) return 7;
   if ("Aug"sv.compare(month) == 0) return 8;
   if ("Sep"sv.compare(month) == 0) return 9;
   if ("Oct"sv.compare(month) == 0) return 10;
   if ("Nov"sv.compare(month) == 0) return 11;
   if ("Dec"sv.compare(month) == 0) return 12;

   return 0;
}

inline constexpr int currentYear()
{
   constexpr std::string_view date{__DATE__};
   constexpr std::string_view year{date.substr(7)};

   return (year[0] - '0') * 1000 + (year[1] - '0') * 100 + (year[2] - '0') * 10 + (year[3] - '0');
}

#define TODO_BEFORE(month, year, todo) \
   static_assert((month > 0 && month <= 12) && \
                 (currentYear() < year || (currentYear() == year && currentMonth() < month)), \
                 "TODO " todo)

#define FIXME_BEFORE(month, year, fix) \
   static_assert((month > 0 && month <= 12) && \
                 (currentYear() < year || (currentYear() == year && currentMonth() < month)), \
                 "FIXME " fix)

