#include "zepch.hpp"

#include "zucchini/Event/Event.hpp"

#include "zucchini/Time/Time.hpp"

namespace ze
{
   Event::Event()
      : m_canceled(false), m_timestamp(Time::Now()) {}

   void Event::cancel() noexcept
   {
      m_canceled = true;
   }

   void Event::setCanceled(bool cancel) noexcept
   {
      m_canceled = cancel;
   }
}
