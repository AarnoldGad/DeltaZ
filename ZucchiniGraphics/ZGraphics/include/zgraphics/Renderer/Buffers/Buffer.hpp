/**
 * Buffer.hpp
 * 13 Sep 2021
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
#ifndef ZG_BUFFER_HPP
#define ZG_BUFFER_HPP

#include "zgraphics/defines.hpp"

namespace zg
{
   class ZG_API Buffer
   {
   public:
      enum class Usage
      {
         Static = 0,
         Dynamic,
      };

      enum class Type
      {
         Vertex = 0,
         Element
      };

      void resize(size_t size);
      void setData(size_t size, void const* data);
      void setSubData(ptrdiff_t offset, size_t size, void const* data);

      template<typename DataType>
      DataType* map();
      void unmap();

      unsigned int getHandle() const noexcept;

      void bind() const noexcept;
      void unbind() const noexcept;

      explicit Buffer(Type bufferType, Usage usage = Usage::Static);
      ~Buffer();

   protected:
      void* map();

      unsigned int m_handle;
      Type const m_type;
      Usage const m_usage;
   };
}

#include "Buffer.inl"

#endif /* ZG_BUFFER_HPP */
