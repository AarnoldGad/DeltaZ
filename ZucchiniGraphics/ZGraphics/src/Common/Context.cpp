#include "zgraphics/Common/Context.hpp"

#include "detail/Common/ContextImpl.hpp"

namespace zg
{
   void Context::Initialise()
   {
      details::ContextImpl::Initialise();
   }

   void Context::LoadAPI()
   {
      details::ContextImpl::LoadAPI();
   }

   void Context::Terminate()
   {
      details::ContextImpl::Terminate();
   }

   void Context::LoadFreetype()
   {
      details::ContextImpl::LoadFreetype();
   }

   void Context::SetActiveContext(Window* window)
   {
      details::ContextImpl::SetActiveContext(window);
   }

   void Context::PollEvents()
   {
      details::ContextImpl::PollEvents();
   }
}

