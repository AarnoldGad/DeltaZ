#include "zgpch.hpp"

#include "zgraphics/Input/Keyboard.hpp"

#include "detail/Input/KeyboardImpl.hpp"

namespace zg
{
   std::string Keyboard::GetKeyName(Key key)
   {
      return details::KeyboardImpl::GetKeyName(key);
   }

   int Keyboard::GetKeyScancode(Key key)
   {
      return details::KeyboardImpl::GetKeyScancode(key);
   }

   bool Keyboard::IsKeyPressed(Key key)
   {
      return details::KeyboardImpl::IsKeyPressed(key);
   }

   uint32_t Keyboard::GetModifiers()
   {
      return details::KeyboardImpl::GetModifiers();
   }
}
