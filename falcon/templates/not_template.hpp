#ifndef _FALCON_TEMPLATES_NOT_TEMPLATE_HPP
#define _FALCON_TEMPLATES_NOT_TEMPLATE_HPP

namespace falcon {

#if __cplusplus >= 201103L
	template<template<class...> class _Temp>
	struct template_not
	{
		template<typename... _Args>
		struct filter
		{
			static const bool value = !_Temp<_Args...>::value;
		};
	};
#else
	template<template<class> class _Temp>
	struct template_not
	{
		template<typename _T>
		struct filter
		{
			static const bool value = !_Temp<_T>::value;
		};
	};
#endif


}

#endif