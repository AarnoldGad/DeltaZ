inline Geometry::operator bool() const noexcept
{
   return m_armatures.size();
}

inline float Geometry::getPrecision() const noexcept
{
   return m_precision;
}

inline Mode Geometry::getMode() const noexcept
{
   return m_mode;
}

inline int Geometry::getIterations() const noexcept
{
   return m_iterations;
}

inline std::vector<Geometry::Armature>& Geometry::getArmatures() noexcept
{
   return m_armatures;
}

inline std::vector<Geometry::Armature> const& Geometry::getArmatures() const noexcept
{
   return m_armatures;
}

