#include "zgpch.hpp"

#include "detail/Input/MouseImpl.hpp"

namespace zg { namespace details
{
   namespace
   {
      static int ModeToGLFWMode(Mouse::CursorMode mode)
      {
         switch (mode)
         {
            case Mouse::CursorMode::Disabled: return GLFW_CURSOR_DISABLED;
            case Mouse::CursorMode::Hidden:   return GLFW_CURSOR_HIDDEN;
            case Mouse::CursorMode::Normal:   return GLFW_CURSOR_NORMAL;
         }

         ZE_ASSERT(false, "Unknown cursor mode !");
         return 0;
      }
   }

   Window* MouseImpl::s_window = nullptr;

   void MouseImpl::SetFocusedWindow(Window* window)
   {
      s_window = window;
   }

   std::string MouseImpl::GetButtonName(Mouse::Button button)
   {
      switch (button)
      {
         case Mouse::Button::Left:
            return "Left";
         case Mouse::Button::Right:
            return "Right";
         case Mouse::Button::Middle:
            return "Middle";
         case Mouse::Button::X1:
            return "X1";
         case Mouse::Button::X2:
            return "X2";
         case Mouse::Button::X3:
            return "X3";
         case Mouse::Button::X4:
            return "X4";
         case Mouse::Button::X5:
            return "X5";
         default:
            return "Unknown";
      }
   }

   bool MouseImpl::IsButtonPressed(Mouse::Button button)
   {
      if (!s_window) return false;

      return static_cast<bool>(glfwGetMouseButton(static_cast<GLFWwindow*>(s_window->getHandle()),
                               static_cast<int>(button)));
   }

   glm::ivec2 MouseImpl::GetPosition()
   {
      if (!s_window) return { 0,0 };

      double x, y;
      glfwGetCursorPos(static_cast<GLFWwindow*>(s_window->getHandle()), &x, &y);
      return { glm::floor(x), glm::floor(y) };
   }

   void MouseImpl::SetPosition(glm::ivec2 pos)
   {
      if (!s_window) return;

      glfwSetCursorPos(static_cast<GLFWwindow*>(s_window->getHandle()), static_cast<double>(pos.x), static_cast<double>(pos.y));
   }

   void MouseImpl::SetCursorMode(Mouse::CursorMode mode)
   {
      if (!s_window) return;

      glfwSetInputMode(static_cast<GLFWwindow*>(s_window->getHandle()), GLFW_CURSOR, ModeToGLFWMode(mode));
   }

   void MouseImpl::SetRawMouseMotion(bool raw)
   {
      if (!s_window) return;

      if (glfwRawMouseMotionSupported())
         glfwSetInputMode(static_cast<GLFWwindow*>(s_window->getHandle()), GLFW_RAW_MOUSE_MOTION, raw ? GLFW_TRUE : GLFW_FALSE);
   }
}}
