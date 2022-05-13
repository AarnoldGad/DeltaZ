inline zg::Window* zg::WindowEvent::getWindow() noexcept
{
   return m_window;
}

inline zg::Window const* zg::WindowEvent::getWindow() const noexcept
{
   return m_window;
}

inline bool zg::WindowFocusedEvent::isFocused() const noexcept
{
   return m_focused;
}

inline bool zg::WindowIconifiedEvent::isIconified() const noexcept
{
   return m_iconified;
}

inline bool zg::WindowMaximisedEvent::isMaximised() const noexcept
{
   return m_maximised;
}

inline glm::ivec2 zg::WindowMovedEvent::getPosition() const noexcept
{
   return m_pos;
}

inline glm::ivec2 zg::WindowMovedEvent::getOffset() const noexcept
{
   return m_offset;
}

inline glm::ivec2 zg::WindowResisedEvent::getSize() const noexcept
{
   return m_size;
}

inline glm::ivec2 zg::WindowResisedEvent::getOffset() const noexcept
{
   return m_offset;
}

inline glm::vec2 zg::WindowScaledEvent::getScale() const noexcept
{
   return m_scale;
}

