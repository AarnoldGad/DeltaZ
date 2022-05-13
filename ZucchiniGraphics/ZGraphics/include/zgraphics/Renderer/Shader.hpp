/**
 * Shader.hpp
 * 4 Sep 2021
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
#ifndef ZG_SHADER_HPP
#define ZG_SHADER_HPP

#include "zgraphics/defines.hpp"

#include <string>
#include <map>

namespace zg
{
   class ZG_API Shader
   {
   public:
      enum class Type
      {
         Vertex = 0,
         Fragment
      };

      void use();

      Status loadSource(char const* vertexSource, char const* fragmentSource);
      Status loadFile(std::filesystem::path const& vertexFile, std::filesystem::path const& fragmentFile);

      void setBoolean(std::string const& var, bool value);
      void setInteger(std::string const& var, int value);
      void setFloat(std::string const& var, float value);

      void setVector2(std::string const& var, glm::vec2 value);
      void setVector3(std::string const& var, glm::vec3 value);
      void setVector4(std::string const& var, glm::vec4 value);

      void setMatrix2(std::string const& var, glm::mat2 value, bool transpose = false);
      void setMatrix3(std::string const& var, glm::mat3 value, bool transpose = false);
      void setMatrix4(std::string const& var, glm::mat4 value, bool transpose = false);

      void setIntegerArray(std::string const& var, int const* value, size_t count);
      void setFloatArray(std::string const& var, float const* value, size_t count);

      //TODO uniform buffer blocks

      unsigned int getHandle() const noexcept;

      Shader(char const* vertex, char const* fragment);
      Shader(std::filesystem::path const& vertex, std::filesystem::path const& fragment);
      Shader();
      ~Shader();

   private:
      std::optional<unsigned int> addShader(Type type, char const* source) noexcept;
      Status linkProgram() noexcept;
      int getUniformLocation(std::string const& var) const noexcept;
      void resetProgram() noexcept;

      Status checkCompileStatus(unsigned int shaderHandle, Type type);
      Status checkLinkStatus();

   private:
      unsigned int m_program;
      mutable std::map<std::string, int> m_uniforms;
   };
}

template<>
class ze::ResourceLoader<zg::Shader>
{
public:
   // TODO Overload to call loadSource in a non-ambiguous way
   static zg::Shader* Load(std::filesystem::path const& vertex, std::filesystem::path const& fragment);
   static void Reload(zg::Shader* shader, std::filesystem::path const& vertex, std::filesystem::path const& fragment);
   static void Unload(zg::Shader* shader);
};

#include "Shader.inl"

#endif /* ZG_SHADER_HPP */
