#include "zgpch.hpp"

#include "zgraphics/Renderer/Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#if defined(_DEBUG)
   #define CHECK_PROGRAM \
      int currentProgram; \
      glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram); \
      if (static_cast<unsigned int>(currentProgram) != m_program) \
         ze::Console::Trace("Currently bound program is different !");
#else
   #define CHECK_PROGRAM
#endif

namespace zg
{
   namespace
   {
      static GLenum TypeToGLShader(Shader::Type type) noexcept
      {
         switch (type)
         {
            case Shader::Type::Vertex:
               return GL_VERTEX_SHADER;
            case Shader::Type::Fragment:
               return GL_FRAGMENT_SHADER;
            default:
               return -1;
         }
      }
   }

   Shader::Shader()
      : m_program(0) {}

   Shader::Shader(std::filesystem::path const& vertex, std::filesystem::path const& fragment)
      : m_program(0)
   {
      loadFile(vertex, fragment);
   }

   Shader::Shader(char const* vertex, char const* fragment)
      : m_program(0)
   {
      loadSource(vertex, fragment);
   }

   Status Shader::loadFile(std::filesystem::path const& vertexFile, std::filesystem::path const& fragmentFile)
   {
      std::optional<std::string> vertexSource   = ze::FileUtils::GetFileContent(vertexFile);
      std::optional<std::string> fragmentSource = ze::FileUtils::GetFileContent(fragmentFile);

      if (vertexSource && fragmentSource)
         return loadSource(vertexSource.value().c_str(), fragmentSource.value().c_str());

      return Status::Error;
   }

   Status Shader::loadSource(char const* vertexSource, char const* fragmentSource)
   {
      resetProgram();

      using ShaderHandle = std::optional<unsigned int>;
      ShaderHandle vertexShader = addShader(Type::Vertex, vertexSource);
      ShaderHandle fragmentShader = addShader(Type::Fragment, fragmentSource);

      if (!vertexShader || !fragmentShader) return Status::Error;

      Status status = linkProgram();

      glDeleteShader(vertexShader.value());
      glDeleteShader(fragmentShader.value());

      return status;
   }

   std::optional<unsigned int> Shader::addShader(Type type, char const* source) noexcept
   {
      unsigned int shader = glCreateShader(TypeToGLShader(type));

      //TODO OpenGL error handling
      glShaderSource(shader, 1, &source, nullptr);
      glCompileShader(shader);

      if (checkCompileStatus(shader, type) == Status::Error)
         return std::nullopt;

      glAttachShader(m_program, shader);

      return shader;
   }

   Status Shader::linkProgram() noexcept
   {
      glLinkProgram(m_program);
      return checkLinkStatus();
   }

   Status Shader::checkCompileStatus(unsigned int shader, Type type)
   {
      int success;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
         char log[512];
         glGetShaderInfoLog(shader, 512, nullptr, log);
         ze::Console::Trace("Fail to compile {} shader : {}",
                            (type == Type::Vertex ? "vertex" : (type == Type::Fragment ? "fragment" : "unknown")),
                            log);

         glDeleteShader(shader);

         return Status::Error;
      }

      return Status::OK;
   }

   Status Shader::checkLinkStatus()
   {
      int success;
      glGetProgramiv(m_program, GL_LINK_STATUS, &success);
      if (!success)
      {
         char log[512];
         glGetProgramInfoLog(m_program, 512, NULL, log);
         ze::Console::Trace("Fail to link shader program : {}", log);

         resetProgram();

         return Status::Error;
      }

      return Status::OK;
   }

   void Shader::setBoolean(std::string const& var, bool value)
   {
      setInteger(var, value ? 1 : 0);
   }

   void Shader::setInteger(std::string const& var, int value)
   {
      CHECK_PROGRAM;
      glUniform1i(getUniformLocation(var), value);
   }

   void Shader::setFloat(std::string const& var, float value)
   {
      CHECK_PROGRAM;
      glUniform1f(getUniformLocation(var), value);
   }

   void Shader::setVector2(std::string const& var, glm::vec2 value)
   {
      CHECK_PROGRAM;
      glUniform2f(getUniformLocation(var), value.x, value.y);
   }

   void Shader::setVector3(std::string const& var, glm::vec3 value)
   {
      CHECK_PROGRAM;
      glUniform3f(getUniformLocation(var), value.x, value.y, value.z);
   }

   void Shader::setVector4(std::string const& var, glm::vec4 value)
   {
      CHECK_PROGRAM;
      glUniform4f(getUniformLocation(var), value.x, value.y, value.z, value.w);
   }

   void Shader::setMatrix2(std::string const& var, glm::mat2 value, bool transpose)
   {
      CHECK_PROGRAM;
      glUniformMatrix2fv(getUniformLocation(var), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
   }

   void Shader::setMatrix3(std::string const& var, glm::mat3 value, bool transpose)
   {
      CHECK_PROGRAM;
      glUniformMatrix3fv(getUniformLocation(var), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
   }

   void Shader::setMatrix4(std::string const& var, glm::mat4 value, bool transpose)
   {
      CHECK_PROGRAM;
      glUniformMatrix4fv(getUniformLocation(var), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
   }

   void Shader::setIntegerArray(std::string const& var, int const* value, size_t count)
   {
      CHECK_PROGRAM;
      glUniform1iv(getUniformLocation(var), static_cast<GLsizei>(count), value);
   }

   void Shader::setFloatArray(std::string const& var, float const* value, size_t count)
   {
      CHECK_PROGRAM;
      glUniform1fv(getUniformLocation(var), static_cast<GLsizei>(count), value);
   }

   int Shader::getUniformLocation(std::string const& var) const noexcept
   {
      auto uniform = m_uniforms.find(var);
      if (uniform == m_uniforms.end())
      {
         int location = glGetUniformLocation(m_program, var.c_str());

         #if defined(_DEBUG)
            if (location == -1)
               ze::Console::Trace("Fail to retrieve uniform location for {} !", var.c_str());
            else
               m_uniforms.insert(std::make_pair(var, location));
         #else
            if (location != -1)
               m_uniforms.insert(std::make_pair(var, location));
         #endif

         return location;
      }

      return uniform->second;
   }

   void Shader::resetProgram() noexcept
   {
      if (m_program)
         glDeleteProgram(m_program);
      m_program = glCreateProgram();
   }

   void Shader::use()
   {
      glUseProgram(m_program);
   }

   Shader::~Shader()
   {
      if (m_program)
         glDeleteProgram(m_program);
   }
}
