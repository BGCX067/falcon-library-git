#ifndef _FALCON_TUPLE_IOSTREAM_HPP
#define _FALCON_TUPLE_IOSTREAM_HPP

#include <falcon/tuple/istream.hpp>
#include <falcon/tuple/ostream.hpp>

namespace tuple {
	namespace iostream {
		using ::falcon::tuple::istream::operator<<;
		using ::falcon::tuple::ostream::operator>>;
	}
}

#endif