#include "zepch.hpp"

#include "zucchini/Event/EventDispatcher.hpp"

namespace ze
{
   EventDispatcher::EventDispatcher(Event& event) noexcept
      : m_event(&event) {}
}
