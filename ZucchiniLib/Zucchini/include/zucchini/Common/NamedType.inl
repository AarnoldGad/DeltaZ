template<typename Type, typename Parameter, template<typename> class... Capabilities>
ze::NamedType<Type, Parameter, Capabilities...>::NamedType(Type const& value)
   : m_value(value) {}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
template<typename Type_>
ze::NamedType<Type, Parameter, Capabilities...>::NamedType(Type&& value, std::enable_if_t<!std::is_reference_v<Type_>, std::nullptr_t>)
   : m_value(std::move(value)) {}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
ze::NamedType<Type, Parameter, Capabilities...>::operator Type&() noexcept
{
   return m_value;
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
ze::NamedType<Type, Parameter, Capabilities...>::operator Type const&() const noexcept
{
   return m_value;
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type& ze::NamedType<Type, Parameter, Capabilities...>::get() noexcept
{
   return m_value;
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type const& ze::NamedType<Type, Parameter, Capabilities...>::get() const noexcept
{
   return m_value;
}

