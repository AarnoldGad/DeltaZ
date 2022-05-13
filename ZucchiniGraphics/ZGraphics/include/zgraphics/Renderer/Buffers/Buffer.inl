inline unsigned int zg::Buffer::getHandle() const noexcept
{
   return m_handle;
}

template<typename DataType>
inline DataType* zg::Buffer::map()
{
   return static_cast<DataType*>(map());
}

