#include "zgraphics/Window/Event/WindowEvents.hpp"

namespace zg
{
   WindowEvent::WindowEvent(Window* window)
      : m_window(window) {}

   WindowClosedEvent::WindowClosedEvent(Window* window)
      : WindowEvent(window) {}

   std::string WindowClosedEvent::toString() const
   {
      std::stringstream debugStr;
      debugStr << "Window " << std::hex << m_window << std::dec << " closed";
      return debugStr.str();
   }

   WindowFocusedEvent::WindowFocusedEvent(Window* window, bool focused)
      : WindowEvent(window), m_focused(focused) {}

   std::string WindowFocusedEvent::toString() const
   {
      std::stringstream debugStr;
      debugStr << "Window " << std::hex << m_window << std::dec << (isFocused() ? " focused" : " unfocused");
      return debugStr.str();
   }

   WindowIconifiedEvent::WindowIconifiedEvent(Window* window, int iconified)
      : WindowEvent(window), m_iconified(static_cast<bool>(iconified)) {}

   std::string WindowIconifiedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Window " << std::hex << m_window << std::dec
      << (isIconified() ? " iconified" : " restored");

      return debugStr.str();
   }

   WindowMaximisedEvent::WindowMaximisedEvent(Window* window, int maximised)
      : WindowEvent(window), m_maximised(static_cast<bool>(maximised)) {}

   std::string WindowMaximisedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Window " << std::hex << m_window << std::dec
      << (isMaximised() ? " maximised" : " minimised");

      return debugStr.str();
   }

   WindowMovedEvent::WindowMovedEvent(Window* window, glm::ivec2 newPos, glm::ivec2 oldPos)
      : WindowEvent(window), m_pos(newPos), m_offset(newPos - oldPos) {}

   std::string WindowMovedEvent::toString() const
   {
      std::stringstream debugStr;
      debugStr << "Window " << std::hex << m_window << std::dec
               << " moved from (" << (m_pos.x - m_offset.x) << "," << (m_pos.y - m_offset.y)
               << ") to (" << m_pos.x << "," << m_pos.y << ")";
      return debugStr.str();
   }

   WindowRefreshedEvent::WindowRefreshedEvent(Window* window)
      : WindowEvent(window) {}

   std::string WindowRefreshedEvent::toString() const
   {
      std::stringstream debugStr;
      debugStr << "Window " << std::hex << m_window << std::dec << " refreshed";
      return debugStr.str();
   }

   WindowResisedEvent::WindowResisedEvent(Window* window, glm::ivec2 newSize, glm::ivec2 oldSize)
      : WindowEvent(window), m_size(newSize), m_offset(newSize - oldSize) {}

   std::string WindowResisedEvent::toString() const
   {
      std::stringstream debugStr;
      debugStr << "Window " << std::hex << m_window << std::dec
               << " resised from (" << m_size.x - m_offset.x << ", " << m_size.y - m_offset.y
               << ") to (" << m_size.x << ", " << m_size.y << ")";
      return debugStr.str();
   }

   WindowScaledEvent::WindowScaledEvent(Window* window, float xscale, float yscale)
      : WindowEvent(window), m_scale{xscale, yscale} {}

   std::string WindowScaledEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Window " << std::hex << m_window << std::dec
      << " scaled by (" << getScale().x << ", " << getScale().y << ")";

      return debugStr.str();
   }
}

