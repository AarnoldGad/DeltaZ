/**
 * Arguments.hpp
 * 12 Oct 2021
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
#ifndef ZE_ARGUMENTS_HPP
#define ZE_ARGUMENTS_HPP

#include "zucchini/defines.hpp"
#include "zucchini/Debug/TodoBefore.hpp"

#include <string>
#include <vector>

TODO_BEFORE(7, 2022, "Better program arguments parsing and standard (like -p/--param style arguments, with values etc)");
namespace ze
{
   class ZE_API Arguments
   {
   public:
      struct Argument
      {
         std::string value;
      };

      void configure(int argc, char* argv[]);
      Argument const* getArgument(size_t index) const;

      size_t size() const noexcept;
      Argument const* operator[](size_t index) const;

      std::vector<Argument>::const_iterator find(std::string const& value) const;

      std::vector<Argument>::const_iterator begin() const;
      std::vector<Argument>::const_iterator end() const;
      std::vector<Argument>::const_reverse_iterator rbegin() const;
      std::vector<Argument>::const_reverse_iterator rend() const;

      Arguments(int argc, char* argv[]);
      Arguments() = default;

   private:
      std::vector<Argument> m_arguments;
   };
}

#include "Arguments.inl"

#endif /* ZE_ARGUMENTS_HPP */
