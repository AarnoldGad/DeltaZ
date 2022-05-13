template<typename Type, template<typename> class crtpType>
inline Type& ze::crtp<Type, crtpType>::underlying() noexcept
{
   return static_cast<Type&>(*this);
}

template<typename Type, template<typename> class crtpType>
inline Type const& ze::crtp<Type, crtpType>::underlying() const noexcept
{
   return static_cast<Type const&>(*this);
}

