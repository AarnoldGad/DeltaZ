/**
 * CRTP.hpp
 * 12 May 2022
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
#ifndef ZE_CRTP_HPP
#define ZE_CRTP_HPP

// CRTP helper from https://www.fluentcpp.com/2017/05/19/crtp-helper/

#include "zucchini/defines.hpp"

namespace ze
{
   template<typename Type, template<typename> class crtpType>
   class crtp
   {
   public:
      Type& underlying() noexcept;
      Type const& underlying() const noexcept;

   private:
      crtp() = default;

      friend crtpType<Type>;
   };
}

#include "CRTP.inl"

#endif // ZE_CRTP_HPP
