#ifndef _FALCON_TUPLE_TUPLE_APPLY_HPP
#define _FALCON_TUPLE_TUPLE_APPLY_HPP

#include <falcon/tuple/parameter_index.hpp>

namespace falcon {

template <typename _Function, typename _Tuple, std::size_t... _Indexes>
constexpr auto tuple_apply(const parameter_index<_Indexes...>&,
													 _Function&& __func, _Tuple&& __t)
-> decltype(__func(std::get<_Indexes>(std::forward<_Tuple>(__t))...))
{ return __func(std::get<_Indexes>(std::forward<_Tuple>(__t))...); }

template <typename _Function, typename _Tuple,
	typename _Indexes = typename build_tuple_index<typename std::decay<_Tuple>::type>::type
>
constexpr auto tuple_apply(_Function&& __func, _Tuple&& __t)
-> decltype(tuple_apply(_Indexes(), std::forward<_Function>(__func), std::forward<_Tuple>(__t)))
{ return tuple_apply(_Indexes(), std::forward<_Function>(__func), std::forward<_Tuple>(__t)); }

}

#endif