#include "zgraphics/Input/Event/MouseEvents.hpp"

namespace zg
{
   MouseEvent::MouseEvent(Window* window, glm::ivec2 pos)
      : m_window(window), m_pos(pos) {}

   MouseMovedEvent::MouseMovedEvent(Window* window, glm::ivec2 pos)
      : MouseEvent(window, pos) {}

   std::string MouseMovedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Mouse moved to (" << m_pos.x << ", " << m_pos.y << ")";

      return debugStr.str();
   }

   MouseEnteredEvent::MouseEnteredEvent(Window* window, glm::ivec2 pos, bool entered)
      : MouseEvent(window, pos), m_entered(entered) {}

   std::string MouseEnteredEvent::toString() const
   {
      return hasEntered() ? "Mouse entered" : "Mouse leaved";
   }

   MouseScrolledEvent::MouseScrolledEvent(Window* window, glm::ivec2 pos, double xoffset, double yoffset)
      : MouseEvent(window, pos), m_xoffset(xoffset), m_yoffset(yoffset) {}

   std::string MouseScrolledEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Mouse scrolled by (" << m_xoffset << ", " << m_yoffset << ")";

      return debugStr.str();
   }

   MouseDroppedEvent::MouseDroppedEvent(Window* window, glm::ivec2 pos, size_t count, char const* paths[])
      : MouseEvent(window, pos), m_paths{}
   {
      for (size_t i = 0; i < count; i++)
         m_paths.push_back(paths[i]);
   }

   std::string MouseDroppedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Mouse dropped on (" << m_pos.x << ", " << m_pos.y << ")";

      std::for_each(m_paths.begin(), m_paths.end(),
                    [&debugStr](std::filesystem::path const& file) { debugStr << "\n\t" << file.string(); });

      return debugStr.str();
   }

   MouseButtonEvent::MouseButtonEvent(Window* window, glm::ivec2 pos, Mouse::Button button, Action action, uint32_t modifiers)
      : MouseEvent(window, pos), m_button(button), m_action(action), m_modifiers(modifiers) {}

   MouseButtonPressedEvent::MouseButtonPressedEvent(Window* window, glm::ivec2 pos, Mouse::Button button, uint32_t modifiers)
      : MouseButtonEvent(window, pos, button, Action::Pressed, modifiers){}

   std::string MouseButtonPressedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Mouse button " << static_cast<int>(m_button)
      << " pressed at (" << m_pos.x << ", " << m_pos.y << ")";

      return debugStr.str();
   }

   MouseButtonReleasedEvent::MouseButtonReleasedEvent(Window* window, glm::ivec2 pos, Mouse::Button button, uint32_t modifiers)
      : MouseButtonEvent(window, pos, button, Action::Released, modifiers) {}

   std::string MouseButtonReleasedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Mouse button " << static_cast<int>(m_button)
               << " released at (" << m_pos.x << ", " << m_pos.y << ")";

      return debugStr.str();
   }
}
