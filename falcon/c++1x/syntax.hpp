#ifndef FALCON_CPP1X_SYNTAX_HPP
#define FALCON_CPP1X_SYNTAX_HPP

#include <falcon/config.hpp>
#include <falcon/c++1x/assignable.hpp>
#include <falcon/c++/initialize.hpp>

#if __cplusplus < 201103L
# define CPP1X_PROTO(_Func, ...) undetermined_type _Func
#else
# if defined(IN_IDE_PARSER)
#  define CPP1X_PROTO(_Func,. type..) auto _Func -> type
# else
#  define CPP1X_PROTO(_Func, ...) auto _Func -> __VA_ARGS__
# endif
#endif

# define CPP1X CPP_INITIALIZE

#if defined(IN_IDE_PARSER)
# define CPP1X_DELEGATE_FUNCTION(_Func, impl...)\
	CPP1X_PROTO(_Func, decltype(impl)) { return impl; }
#else
# define CPP1X_DELEGATE_FUNCTION(_Func, ...)\
	CPP1X_PROTO(_Func, decltype(__VA_ARGS__)) { return __VA_ARGS__; }
#endif

#endif