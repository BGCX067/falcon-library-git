#ifndef _FALCON_ACCESSOR_BASE_ACCESSOR_HPP
#define _FALCON_ACCESSOR_BASE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template <typename _Class, typename _T = typename _Class::base_type&>
struct base_accessor
{
	typedef _T result_type;
	typedef _Class argument_type;

	result_type operator()(_Class& cont) const
	{
		return cont.base();
	}

	CPP_CONSTEXPR_OR_CONST result_type operator()(const _Class& cont) const
	{
		return cont.base();
	}
};

}

#endif