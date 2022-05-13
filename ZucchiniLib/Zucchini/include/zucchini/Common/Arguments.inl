inline size_t ze::Arguments::size() const noexcept
{
   return m_arguments.size();
}

inline ze::Arguments::Argument const* ze::Arguments::getArgument(size_t index) const
{
   return &m_arguments.at(index);
}

inline ze::Arguments::Argument const* ze::Arguments::operator[](size_t index) const
{
   return getArgument(index);
}

inline std::vector<ze::Arguments::Argument>::const_iterator ze::Arguments::begin() const
{
   return m_arguments.begin();
}

inline std::vector<ze::Arguments::Argument>::const_iterator ze::Arguments::end() const
{
   return m_arguments.end();
}

inline std::vector<ze::Arguments::Argument>::const_reverse_iterator ze::Arguments::rbegin() const
{
   return m_arguments.rbegin();
}

inline std::vector<ze::Arguments::Argument>::const_reverse_iterator ze::Arguments::rend() const
{
   return m_arguments.rend();
}

