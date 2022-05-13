#include "zgpch.hpp"

#include "zgraphics/Input/Mouse.hpp"

#include "detail/Input/MouseImpl.hpp"

namespace zg
{
   std::string Mouse::GetButtonName(Button button)
   {
      return details::MouseImpl::GetButtonName(button);
   }

   bool Mouse::IsButtonPressed(Button button)
   {
      return details::MouseImpl::IsButtonPressed(button);
   }

   glm::ivec2 Mouse::GetPosition()
   {
      return details::MouseImpl::GetPosition();
   }

   void Mouse::SetPosition(glm::ivec2 pos)
   {
      details::MouseImpl::SetPosition(pos);
   }

   void Mouse::SetCursorMode(CursorMode mode)
   {
      details::MouseImpl::SetCursorMode(mode);
   }

   void Mouse::SetRawMouseMotion(bool raw)
   {
      details::MouseImpl::SetRawMouseMotion(raw);
   }
}
