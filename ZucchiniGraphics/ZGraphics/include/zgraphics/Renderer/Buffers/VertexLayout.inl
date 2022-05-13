inline size_t zg::VertexAttribute::GetTypeSize(Type type) noexcept
{
   switch (type)
   {
      case Type::Float:
         return 4;
      case Type::Vec2:
         return 4 * 2;
      case Type::Vec3:
         return 4 * 3;
      case Type::Vec4:
         return 4 * 4;
      case Type::Mat3:
         return 4 * 3 * 3;
      case Type::Mat4:
         return 4 * 4 * 4;
      case Type::Int:
         return 4;
      case Type::Bool:
         return 4;
      default:
         return 0;
   }
}

inline size_t zg::VertexLayout::getStride() const noexcept
{
   return m_stride;
}

inline std::vector<zg::VertexAttribute> const& zg::VertexLayout::getAttributes() const noexcept
{
   return m_attributes;
}

inline zg::VertexAttribute const& zg::VertexLayout::getAttribute(size_t index) const
{
   return m_attributes[index];
}

inline zg::VertexAttribute const& zg::VertexLayout::operator[](size_t index) const
{
   return getAttribute(index);
}

inline std::vector<zg::VertexAttribute>::const_iterator zg::VertexLayout::begin() const noexcept
{
   return m_attributes.begin();
}

inline std::vector<zg::VertexAttribute>::const_iterator zg::VertexLayout::end() const noexcept
{
   return m_attributes.end();
}

