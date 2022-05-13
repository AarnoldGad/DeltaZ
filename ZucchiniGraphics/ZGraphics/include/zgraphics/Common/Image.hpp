/**
 * Image.hpp
 * 2021
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
#ifndef ZG_IMAGE_HPP
#define ZG_IMAGE_HPP

#include "zgraphics/defines.hpp"

#include <zucchini/Common/Console.hpp>

// TODO Use smart pointers
namespace zg
{
   class ZG_API Image
   {
   public:
      enum class Format : uint32_t
      {
         Unknown = 0,
         Grey, //<- 1 8-bit channel
         GreyAlpha, //<- 2 8-bit channels
         RGB, //<- 3 8-bit channels
         RGBA //<- 4 8-bit channels
      };

      static void FlipOnLoad(bool flip);

      uint8_t const* getData() const noexcept;
      Format getFormat() const noexcept;
      glm::ivec2 getSize() const noexcept;

      explicit operator bool() const noexcept;

      Status loadFile(std::filesystem::path const& file, Format desiredFormat = Format::Unknown);
      bool isLoaded() const noexcept;
      void unload() noexcept;

      explicit Image(std::filesystem::path const& file, Format desiredFormat = Format::Unknown);

      Image(Image const& other);
      Image(Image&&);
      Image& operator=(Image const&);
      Image& operator=(Image&&);

      Image();
      ~Image();

   private:
      uint8_t* m_data;
      Format m_format;
      glm::ivec2 m_size;
   };
}

template<>
class ze::ResourceLoader<zg::Image>
{
public:
   static zg::Image* Load(std::filesystem::path const& file,
                          zg::Image::Format format = zg::Image::Format::Unknown);
   static void Reload(zg::Image* image, std::filesystem::path const& file,
                            zg::Image::Format format = zg::Image::Format::Unknown);
   static void Unload(zg::Image* image);
};

#include "Image.inl"

#endif /* ZG_IMAGE_HPP */
