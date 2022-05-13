#include "zgraphics/Input/Event/KeyEvents.hpp"

namespace zg
{
   KeyEvent::KeyEvent(Window* window, Keyboard::Key key, int scancode, Action action, uint32_t modifiers)
      : m_window(window), m_key(key), m_scancode(scancode), m_action(action), m_modifiers(modifiers) {}

   KeyPressedEvent::KeyPressedEvent(Window* window, Keyboard::Key key, int scancode, uint32_t modifiers)
      : KeyEvent(window, key, scancode, Action::Pressed, modifiers) {}

   std::string KeyPressedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Key " << static_cast<int>(m_key) << " pressed";

      return debugStr.str();
   }

   KeyReleasedEvent::KeyReleasedEvent(Window* window, Keyboard::Key key, int scancode, uint32_t modifiers)
      : KeyEvent(window, key, scancode, Action::Released, modifiers) {}

   std::string KeyReleasedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Key " << static_cast<int>(m_key) << " released";

      return debugStr.str();
   }

   KeyRepeatedEvent::KeyRepeatedEvent(Window* window, Keyboard::Key key, int scancode, uint32_t modifiers)
      : KeyEvent(window, key, scancode, Action::Repeated, modifiers) {}

   std::string KeyRepeatedEvent::toString() const
   {
      std::stringstream debugStr;

      debugStr << "Key " << static_cast<int>(m_key) << " repeated";

      return debugStr.str();
   }
}

