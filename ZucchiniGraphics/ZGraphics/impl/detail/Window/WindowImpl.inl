inline void* zg::details::WindowImpl::getHandle() noexcept
{
   return m_handle;
}

inline ze::EventBus* zg::details::WindowImpl::getEventBus() const noexcept
{
   return m_eventBus;
}

inline std::string const& zg::details::WindowImpl::getTitle() const
{
   return m_title;
}

inline glm::ivec2 zg::details::WindowImpl::getSize() const
{
   int width, height;
   glfwGetWindowSize(m_handle, &width, &height);
   return { width, height };
}

inline glm::ivec2 zg::details::WindowImpl::getFramebufferSize() const
{
   int width, height;
   glfwGetFramebufferSize(m_handle, &width, &height);
   return { width, height };
}

// TODO
// inline zg::Image const& zg::details::WindowImpl::getIcon() const
// {
// 
// }

inline glm::ivec2 zg::details::WindowImpl::getPosition() const
{
   int x, y;
   glfwGetWindowPos(m_handle, &x, &y);
   return { x, y };
}

inline float zg::details::WindowImpl::getOpacity() const
{
   return glfwGetWindowOpacity(m_handle);
}

inline bool zg::details::WindowImpl::isVisible() const
{
   return static_cast<bool>(glfwGetWindowAttrib(m_handle, GLFW_VISIBLE));
}

inline bool zg::details::WindowImpl::shouldClose() const
{
   return static_cast<bool>(glfwWindowShouldClose(m_handle));
}

inline glm::vec4 zg::details::WindowImpl::getColor() const
{
   return m_color;
}

template<typename EventType, typename... Args>
inline void zg::details::WindowImpl::PushEvent(GLFWwindow* window, Args&&... args)
{
   WindowImpl* windowPtr = reinterpret_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
   if (windowPtr->m_eventBus)
      windowPtr->m_eventBus->pushEvent<EventType>(windowPtr->m_root, std::forward<Args>(args)...);
}

template<typename EventType>
inline void zg::details::WindowImpl::PushKeyEvent(GLFWwindow* window, int key, int scancode, int modifiers)
{
   PushEvent<EventType>(window, static_cast<Keyboard::Key>(key), scancode, static_cast<uint32_t>(modifiers));
}

template<typename EventType, typename... Args>
inline void zg::details::WindowImpl::PushMouseEvent(GLFWwindow* window, Args&&... args)
{
   double x, y;
   glfwGetCursorPos(window, &x, &y);
   glm::ivec2 pos = { glm::floor(x), glm::floor(y) };

   PushEvent<EventType>(window, pos, std::forward<Args>(args)...);
}

