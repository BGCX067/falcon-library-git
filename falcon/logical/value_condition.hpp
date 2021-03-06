#ifndef _FALCON_LOGICAL_VALUE_CONDITION_HPP
#define _FALCON_LOGICAL_VALUE_CONDITION_HPP

namespace falcon {

#if __cplusplus >= 201103L
template<typename _T>
inline constexpr _T& first_true(_T& a)
{
	return a;
}

template<typename _T, typename... _Args>
inline constexpr _T& first_true(_T& a, _Args&... args)
{
	return a ? a : first_true<_T>(args...);
}

#else
template<typename _T>
inline _T& first_true(_T& a, _T& b)
{
	return a ? a : b;
}
#endif

#if __cplusplus >= 201103L
template<typename _T>
inline constexpr _T& first_false(_T& a)
{
	return a;
}

template<typename _T, typename... _Args>
inline constexpr _T& first_false(_T& a, _Args&... args)
{
	return a ? first_false<_T>(args...) : a;
}

#else
template<typename _T>
inline _T& first_false(_T& a, _T& b)
{
	return a ? b : a;
}
#endif

}

#endif
