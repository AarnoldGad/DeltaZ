#include "detail/Common/ContextImpl.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace zg { namespace details
{
   FT_Library ContextImpl::s_freetype = nullptr;
   bool ContextImpl::s_isInitialised = false;
   bool ContextImpl::s_isFreetypeLoaded = false;

   void ContextImpl::Initialise()
   {
      if (s_isInitialised) return;

      glfwSetErrorCallback(&ContextImpl::HandleGLFWError);

      // TODO Restore logging system
      ze::Console::Print("------ * Initialising GLFW...");
      ze::Console::Print("------    * GLFW Compiled against {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
      int major, minor, rev;
      glfwGetVersion(&major, &minor, &rev);
      ze::Console::Print("------    * GLFW Linked against {}.{}.{}", major, minor, rev);

      if (!glfwInit())
         ze::RaiseCritical(-1, "Fail to initialise GLFW !");

      s_isInitialised = true;
   }

   void ContextImpl::LoadAPI()
   {
      ze::Console::Print("------ * Loading OpenGL...");

      if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
         ze::RaiseCritical(-1, "Fail to load OpenGL !");

      ze::Console::Print("------    * OpenGL   {}", glGetString(GL_VERSION));
      ze::Console::Print("------    * Vendor   {}", glGetString(GL_VENDOR));
      ze::Console::Print("------    * Graphics {}", glGetString(GL_RENDERER));
      ze::Console::Print("------    * GLSL     {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
   }

   void ContextImpl::LoadFreetype()
   {
      if (s_isFreetypeLoaded) return;

      ze::Console::Print("------ * Loading Freetype...");
      FT_Error error = FT_Init_FreeType(&s_freetype);
      if (error)
         ze::RaiseCritical(-1, "Fail to load Freetype!");

      int major, minor, patch;
      FT_Library_Version(s_freetype, &major, &minor, &patch);

      ze::Console::Print("------    * Freetype compile against {}.{}.{}", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH);
      ze::Console::Print("------    * Freetype linked against {}.{}.{}", major, minor, patch);

      s_isFreetypeLoaded = true;
   }

   void ContextImpl::Terminate()
   {
      if (s_isInitialised)
      {
         ze::Console::Print("------ * Terminating GLFW");
         glfwTerminate();
         s_isInitialised = false;
      }

      if (s_isFreetypeLoaded)
      {
         ze::Console::Print("------ * Unloading Freetype");
         FT_Done_FreeType(s_freetype);
         s_freetype = nullptr;
         s_isFreetypeLoaded = false;
      }
   }

   void ContextImpl::SetActiveContext(Window* window)
   {
      glfwMakeContextCurrent(static_cast<GLFWwindow*>(window->getHandle()));
   }

   void ContextImpl::PollEvents()
   {
      glfwPollEvents();
   }

   FT_Library ContextImpl::GetFreetype()
   {
      return s_freetype;
   }

   void ContextImpl::HandleGLFWError(int code, char const* description)
   {
      ze::Console::Trace("A GLFW Error occured : ({}) {}", code, description);
   }
}}

