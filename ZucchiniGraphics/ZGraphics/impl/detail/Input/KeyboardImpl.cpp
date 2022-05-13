#include "zgpch.hpp"

#include "detail/Input/KeyboardImpl.hpp"

#include "zgraphics/Input/Event/KeyEvents.hpp"

namespace zg { namespace details
{
   Window* KeyboardImpl::s_window = nullptr;

   void KeyboardImpl::SetFocusedWindow(Window* window)
   {
      s_window = window;
   }

   std::string KeyboardImpl::GetKeyName(Keyboard::Key key)
   {
      char const* name = glfwGetKeyName(static_cast<int>(key), GetKeyScancode(key));
      return name ? name : "";
   }

   int KeyboardImpl::GetKeyScancode(Keyboard::Key key)
   {
      return glfwGetKeyScancode(static_cast<int>(key));
   }

   bool KeyboardImpl::IsKeyPressed(Keyboard::Key key)
   {
      if (!s_window) return false;

      return static_cast<bool>(glfwGetKey(static_cast<GLFWwindow*>(s_window->getHandle()), static_cast<int>(key)));
   }

   uint32_t KeyboardImpl::GetModifiers()
   {
      uint32_t mods = 0;

      mods |= (IsKeyPressed(Keyboard::Key::LeftShift)   || IsKeyPressed(Keyboard::Key::RightShift))
                  ? static_cast<uint32_t>(Keyboard::Modifiers::Shift)    : 0;
      mods |= (IsKeyPressed(Keyboard::Key::LeftControl) || IsKeyPressed(Keyboard::Key::RightControl))
                  ? static_cast<uint32_t>(Keyboard::Modifiers::Ctrl)     : 0;
      mods |= (IsKeyPressed(Keyboard::Key::LeftAlt)     || IsKeyPressed(Keyboard::Key::RightAlt))
                  ? static_cast<uint32_t>(Keyboard::Modifiers::Alt)      : 0;
      mods |= (IsKeyPressed(Keyboard::Key::LeftSuper)   || IsKeyPressed(Keyboard::Key::RightSuper))
                  ? static_cast<uint32_t>(Keyboard::Modifiers::Super)    : 0;
      mods |= (IsKeyPressed(Keyboard::Key::CapsLock))
                  ? static_cast<uint32_t>(Keyboard::Modifiers::CapsLock) : 0;
      mods |= (IsKeyPressed(Keyboard::Key::NumLock))
                  ? static_cast<uint32_t>(Keyboard::Modifiers::NumLock)  : 0;

      return mods;
   }
}}

