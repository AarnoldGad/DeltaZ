inline zg::Window* zg::MouseEvent::getWindow() noexcept
{
   return m_window;
}

inline glm::ivec2 zg::MouseEvent::getPosition() const noexcept
{
   return m_pos;
}

inline bool zg::MouseEnteredEvent::hasEntered() const noexcept
{
   return m_entered;
}

inline bool zg::MouseEnteredEvent::hasLeaved() const noexcept
{
   return !m_entered;
}

inline double zg::MouseScrolledEvent::getHorizontalOffset() const noexcept
{
   return m_xoffset;
}

inline double zg::MouseScrolledEvent::getVerticalOffset() const noexcept
{
   return m_yoffset;
}

inline std::vector<std::filesystem::path> const& zg::MouseDroppedEvent::getPaths() const noexcept
{
   return m_paths;
}

inline std::filesystem::path zg::MouseDroppedEvent::getPath(size_t const index) const
{
   return m_paths.at(index);
}

inline size_t zg::MouseDroppedEvent::getPathCount() const noexcept
{
   return m_paths.size();
}

inline zg::Mouse::Button zg::MouseButtonEvent::getButton() const noexcept
{
   return m_button;
}

inline zg::MouseButtonEvent::Action zg::MouseButtonEvent::getAction() const noexcept
{
   return m_action;
}

inline uint32_t zg::MouseButtonEvent::getModifiers() const noexcept
{
   return m_modifiers;
}

