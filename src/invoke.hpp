#if ! defined(BOOST_PP_IS_ITERATING)
# ifndef N2O_INVOKE_INCLUDED
#  define N2O_INVOKE_INCLUDED

#  include "config.h"

#  include <boost/type_traits/is_member_function_pointer.hpp>
#  include <boost/type_traits/is_same.hpp>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/facilities/intercept.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace n2o { namespace detail {

typedef int void_result_to_js;

template <bool returns_void, bool is_member> struct invoke_tag_ {};

template <typename R, typename F>
struct invoke_tag :
    invoke_tag_<
        boost::is_same<R, void>::value,
        boost::is_member_function_pointer<F>::value
    >
{};

# define BOOST_PP_ITERATION_PARAMS_1 \
    (3, (0, N2O_MAX_ARITY, <invoke.hpp>))
# include BOOST_PP_ITERATE()


}} // end of namespace detail, n2o

# endif // N2O_INVOKE_INCLUDED
#else // ! defined(BOOST_PP_IS_ITERATING)

# define N BOOST_PP_ITERATION()

template <typename RC, typename F BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, typename AC)>
inline
v8::Handle<v8::Value>
invoke(invoke_tag_<false, false>, RC const& rc, F & f BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, &ac))
{
    return rc( f( BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT)));
}

template <typename RC, typename F BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, typename AC)>
inline
v8::Handle<v8::Value>
invoke(invoke_tag_<true, false>, RC const& rc, F & f BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, &ac))
{
    f( BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT));
    return v8::Undefined();
}

template <typename RC, typename F, typename TC BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, typename AC)>
inline
v8::Handle<v8::Value>
invoke(invoke_tag_<false, true>, RC const& rc, F & f, TC & tc BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, &ac))
{
    return rc( (tc().*f)(BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT)) );
}

template <typename RC, typename F, typename TC BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, typename AC)>
inline
v8::Handle<v8::Value>
invoke(invoke_tag_<true, true>, RC const& rc, F & f, TC & tc BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(1, N, AC, &ac))
{
    return (tc().*f)(BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, ac, () BOOST_PP_INTERCEPT));
    return v8::Undefined();
}

# undef N

#endif
