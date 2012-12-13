#ifndef FALCON_FUNCTIONAL_ARGUMENTS_WRAPPER_HPP
#define FALCON_FUNCTIONAL_ARGUMENTS_WRAPPER_HPP

#include <tuple>
#include <falcon/tuple/tuple_apply.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>

namespace falcon
{

/**
 * \code
 * int a = 2, b = 3;
 * arguments_wrapper<int&, int> args(a, b);
 * args(f);
 * \endcode
 * equivalent to
 * \code
 * int a = 2, b = 3;
 * f(a,b);
 * \endcode
 */
template <typename... _Elements>
class arguments_wrapper
: public std::tuple<_Elements...>
{
	typedef std::tuple<_Elements...> __base;

public:
	typedef __base tuple_type;


	constexpr arguments_wrapper() = default;

	explicit constexpr arguments_wrapper(const _Elements&... __elements)
	: __base(__elements...)
	{}

	template<typename... _UElements>
	explicit constexpr arguments_wrapper(_UElements&&... __elements)
	: __base(std::forward<_UElements>(__elements)...)
	{}

	constexpr arguments_wrapper(const tuple_type& t)
	: __base(t)
	{}

	constexpr arguments_wrapper(tuple_type&& t)
	: __base(std::forward<tuple_type>(t))
	{}

	constexpr arguments_wrapper(const arguments_wrapper&) = default;
	constexpr arguments_wrapper(arguments_wrapper&&) = default;
	template<typename... _UElements>
	constexpr arguments_wrapper(arguments_wrapper<_UElements...>&& other)
	: __base(std::forward<std::tuple<_UElements...>>(other))
	{}

	template<typename... _UElements>
	constexpr arguments_wrapper(const std::tuple<_UElements...>& __in)
	: __base(__in)
	{}

	template<typename... _UElements>
	constexpr arguments_wrapper(std::tuple<_UElements...>&& __in)
	: __base(std::forward<std::tuple<_UElements...>>(__in))
	{}

	template<typename _Alloc>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a)
	: __base(__tag, __a)
	{}

	template<typename _Alloc>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a,
					  const _Elements&... __elements)
	: __base(__tag, __a, __elements...)
	{}

	template<typename _Alloc, typename... _UElements>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a,
					  _UElements&&... __elements)
	: __base(__tag, __a, std::forward<_UElements>(__elements)...)
	{}

	template<typename _Alloc>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a,
					  const tuple_type& __in)
	: __base(__tag, __a, __in)
	{}

	template<typename _Alloc>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a,
					  tuple_type&& __in)
	: __base(__tag, __a, __in)
	{}

	template<typename _Alloc, typename... _UElements>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a,
					  const std::tuple<_UElements...>& __in)
	: __base(__tag, __a, __in)
	{}

	template<typename _Alloc, typename... _UElements>
	arguments_wrapper(std::allocator_arg_t __tag, const _Alloc& __a,
					  std::tuple<_UElements...>&& __in)
	: __base(__tag, __a, std::forward<std::tuple<_UElements...>>(__in))
	{}

	using std::tuple<_Elements...>::operator=;

	const tuple_type& tuple() const
	{ return *this; }

	tuple_type& tuple()
	{ return *this; }

	template<typename _Functor>
	auto operator()(_Functor func) const
	-> decltype(tuple_apply<const _Functor&>(func, this->tuple()))
	{ return tuple_apply<const _Functor&>(func, tuple()); }

	template<typename _Functor>
	auto operator()(_Functor func)
	-> decltype(tuple_apply<_Functor&>(func, this->tuple()))
	{ return tuple_apply<_Functor&>(func, tuple()); }

	template<typename _Functor, std::size_t... _Indexes>
	auto operator()(const parameter_index<_Indexes...>& indexes, _Functor func) const
	-> decltype(tuple_apply<const _Functor&>(indexes, func, this->tuple()))
	{ return tuple_apply<const _Functor&>(indexes, func, tuple()); }

	template<typename _Functor, std::size_t... _Indexes>
	auto operator()(const parameter_index<_Indexes...>& indexes, _Functor func)
	-> decltype(tuple_apply<_Functor&>(indexes, func, this->tuple()))
	{ return tuple_apply<_Functor&>(indexes, func, tuple()); }

	void swap(arguments_wrapper& other)
	{ std::swap(tuple(), other.tuple()); }
};

template<typename... _Elements>
constexpr arguments_wrapper<typename decay_and_strip<_Elements>::type...>
make_arguments(_Elements&&... __args)
{
	return arguments_wrapper<
		typename decay_and_strip<_Elements>::type...
	>(std::forward<_Elements>(__args)...);
}

template<typename... _Elements>
constexpr arguments_wrapper<_Elements&&...>
forward_as_arguments(_Elements&&... __args) noexcept
{ return arguments_wrapper<_Elements&&...>(std::forward<_Elements>(__args)...); }

}

namespace std
{
	template<typename... _Elements>
	struct tuple_size<falcon::arguments_wrapper<_Elements...>>
	{ static const int value = sizeof...(_Elements); };

	template<std::size_t _Index, typename... _Elements>
	struct tuple_element<_Index, falcon::arguments_wrapper<_Elements...>>
	: tuple_element<_Index, std::tuple<_Elements...>>
	{};

	template<typename... _Elements>
	void swap(falcon::arguments_wrapper<_Elements...>& a,
			  falcon::arguments_wrapper<_Elements...>& b)
	{ a.swap(b); };
}

#endif
