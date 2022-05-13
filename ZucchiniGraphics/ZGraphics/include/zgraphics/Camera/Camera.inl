inline glm::vec3 zg::Camera::getFront() const noexcept
{
   return m_front;
}

inline glm::vec3 zg::Camera::getUp() const noexcept
{
   return m_up;
}

inline ze::Angle zg::Camera::getFieldOfView() const noexcept
{
   return m_fov;
}

inline float zg::Camera::getAspectRatio() const noexcept
{
   return m_ratio;
}

inline glm::vec3 zg::Camera::getPosition() const noexcept
{
   return m_pos;
}
