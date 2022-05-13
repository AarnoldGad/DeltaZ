inline zg::Window* zg::KeyEvent::getWindow() noexcept
{
   return m_window;
}

inline zg::Keyboard::Key zg::KeyEvent::getKey() const noexcept
{
   return m_key;
}

inline int zg::KeyEvent::getScancode() const noexcept
{
   return m_scancode;
}

inline zg::KeyEvent::Action zg::KeyEvent::getAction() const noexcept
{
   return m_action;
}

inline uint32_t zg::KeyEvent::getModifiers() const noexcept
{
   return m_modifiers;
}
