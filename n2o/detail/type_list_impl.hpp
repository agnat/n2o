#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
# ifndef N2O_DETAIL_TYPE_LIST_IMPL_INCLUDED
#  define N2O_DETAIL_TYPE_LIST_IMPL_INCLUDED

#  include <n2o/settings.hpp>

#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/enum_params_with_a_default.hpp>
#  include <boost/preprocessor/repetition/enum.hpp>
#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/arithmetic/sub.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repetition/enum_trailing.hpp>
//#  include <boost/preprocessor/cat.hpp>

#  include <n2o/detail/type_list.hpp>

namespace n2o { namespace detail {

template <BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N2O_LIST_SIZE, typename T, boost::mpl::void_)>
struct type_list
    : BOOST_PP_CAT(boost::mpl::vector, N2O_LIST_SIZE)<BOOST_PP_ENUM_PARAMS_Z(1, N2O_LIST_SIZE, T)>
{};

#  define BOOST_PP_ITERATION_PARAMS_1 \
        (3, (0, BOOST_PP_DEC(N2O_LIST_SIZE), <n2o/detail/type_list_impl.hpp>))

#  include BOOST_PP_ITERATE()

}} // end of namespace n2o::detail

# endif // N2O_DETAIL_TYPE_LIST_IMPL_INCLUDED

#else // BOOST_PP_IS_ITERATING

# define N BOOST_PP_ITERATION()
# define N2O_VOID_ARGS BOOST_PP_SUB_D(1,N2O_LIST_SIZE,N)

template <
    BOOST_PP_ENUM_PARAMS_Z(1, N, typename T)
    >
struct type_list<
    BOOST_PP_ENUM_PARAMS_Z(1, N, T)
    BOOST_PP_COMMA_IF(N)
    BOOST_PP_ENUM(N2O_VOID_ARGS, N2O_FIXED, boost::mpl::void_)
    >
    : BOOST_PP_CAT(boost::mpl::vector,N)<BOOST_PP_ENUM_PARAMS_Z(1, N, T)>
{};

# undef N2O_VOID_ARGS
# undef N

#endif // BOOST_PP_IS_ITERATING
