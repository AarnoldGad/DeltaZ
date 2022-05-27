inline zg::Transform zg::Transform::Identity() noexcept
{
   static Transform identity;
   return identity;
}

inline glm::vec3 zg::Transform::getPosition() const noexcept
{
   return m_pos;
}

inline glm::vec3 zg::Transform::getOrigin() const noexcept
{
   return m_origin;
}

inline glm::vec3 zg::Transform::getScale() const noexcept
{
   return m_scale;
}

inline glm::quat zg::Transform::getRotation() const noexcept
{
   return m_rotation;
}

