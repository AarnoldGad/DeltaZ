/**
 * VertexLayout.hpp
 * 16 Sep 2021
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
#ifndef ZG_VERTEXLAYOUT_HPP
#define ZG_VERTEXLAYOUT_HPP

#include "zgraphics/defines.hpp"

#include <vector>

namespace zg
{
   struct VertexAttribute
   {
      enum class Type
      {
         Float = 0,
         Vec2,
         Vec3,
         Vec4,
         Int,
         IVec2,
         IVec3,
         IVec4,
         Mat3,
         Mat4,
         Bool
      };

      static size_t GetTypeSize(Type type) noexcept;

      VertexAttribute(Type type, std::string const& name, bool normalised = false)
         : index{}, type(type), name(name), byteSize(GetTypeSize(type)), offset{}, normalised(normalised) {}

      size_t index;
      Type type;
      std::string name;
      size_t byteSize;
      size_t offset;
      bool normalised;
   };

   class ZG_API VertexLayout
   {
   public:
      using Attributes = std::vector<VertexAttribute>;
      using ConstIterator = std::vector<VertexAttribute>::const_iterator;

      void add(VertexAttribute::Type type, std::string const& name, bool normalised = false);
      void add(VertexAttribute&& attribute);

      size_t getStride() const noexcept;

      Attributes const& getAttributes() const noexcept;
      VertexAttribute const& getAttribute(size_t index) const;
      VertexAttribute const& operator[](size_t index) const;

      ConstIterator begin() const noexcept;
      ConstIterator end() const noexcept;

      VertexLayout();

   private:
      Attributes m_attributes;
      size_t m_stride;
   };
}

#include "VertexLayout.inl"

#endif /* ZG_VERTEXLAYOUT_HPP */
