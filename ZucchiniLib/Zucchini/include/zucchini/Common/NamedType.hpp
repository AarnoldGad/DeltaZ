/**
 * NamedType.hpp
 * 11 May 2022
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
#ifndef ZE_NAMEDTYPE_HPP
#define ZE_NAMEDTYPE_HPP

// Inspired by fluentcpp articles on Strong Types

#include "zucchini/defines.hpp"

#include "zucchini/Common/CRTP.hpp"

#include <memory>
#include <type_traits>

namespace ze
{
   // TODO Capabilities Impl
   template<typename Type, typename Parameter, template<typename> class... Capabilities>
   class NamedType : public Capabilities<NamedType<Type, Parameter, Capabilities...> >...
   {
   public:
      explicit NamedType(Type const& value);
      template<typename Type_ = Type>
      explicit NamedType(Type&& value,
                         typename std::enable_if_t<!std::is_reference_v<Type_>, std::nullptr_t> = nullptr);

      explicit operator Type&() noexcept;
      explicit operator Type const&() const noexcept;

      Type& get() noexcept;
      Type const& get() const noexcept;

   private:
      Type m_value;
   };
}

#include "NamedType.inl"

#endif // ZE_NAMEDTYPE_HPP
