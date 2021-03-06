#ifndef FALCON_TYPE_TRAITS_ENABLE_IF_HPP
#define FALCON_TYPE_TRAITS_ENABLE_IF_HPP

namespace falcon {

// Define a nested type if some predicate holds.
template<bool, typename T = void>
struct enable_if
{ typedef T type; };

// Partial specialization for true.
template<typename T>
struct enable_if<false, T>
{};

template<class C, typename T = void>
struct enable_if_c
: enable_if<C::value, T>
{};

}

#endif
