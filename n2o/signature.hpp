#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
# ifndef N2O_SIGNATURE_INCLUDED
#  define N2O_SIGNATURE_INCLUDED

#  include <n2o/config.h>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/type_traits/is_convertible.hpp>
#  include <boost/mpl/if.hpp>

#include <n2o/detail/preprocessor.hpp>
#include <n2o/detail/type_list.hpp>

#  define N2O_LIST_INC(n) \
        BOOST_PP_CAT(boost::mpl::vector, BOOST_PP_INC(n))

namespace n2o { namespace detail {


// A metafunction returning C1 if C1 is derived from C2, and C2
// otherwise
template <class C1, class C2>
struct most_derived
{
    typedef typename boost::mpl::if_<
        boost::is_convertible<C1*,C2*>
      , C1
      , C2
    >::type type;
};


#  define BOOST_PP_ITERATION_PARAMS_1 \
        (3, (0, N2O_MAX_ARITY, <n2o/signature.hpp>))
#  include BOOST_PP_ITERATE()

}} // end of namespace detail, n2o

# endif // N2O_SIGNATURE_INCLUDED

#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

# define N BOOST_PP_ITERATION()

template <class RT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)>
inline
N2O_LIST_INC(N) <RT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)>
get_signature(RT(*)(BOOST_PP_ENUM_PARAMS_Z(1, N, T)), void * = 0) {
    return N2O_LIST_INC(N)<RT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)>();
}

# undef N

# define BOOST_PP_ITERATION_PARAMS_2 \
    (3, (0, 3, <n2o/signature.hpp>))
# include BOOST_PP_ITERATE()

#else // BOOST_PP_ITERATION_DEPTH

# define N BOOST_PP_RELATIVE_ITERATION(1)
# define Q N2O_CV_QUALIFIER(BOOST_PP_ITERATION())

template <class RT, class ClassT BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)>
inline
N2O_LIST_INC(BOOST_PP_INC(N))<RT, ClassT& BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)>
get_signature(RT(ClassT::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, T)) Q) {
    return N2O_LIST_INC(BOOST_PP_INC(N))<RT, ClassT& BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)>();
}

template <
    class Target
  , class RT
  , class ClassT
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, class T)
>
inline N2O_LIST_INC(BOOST_PP_INC(N))<
    RT
  , typename most_derived<Target, ClassT>::type&
    BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)
>
get_signature(
    RT(ClassT::*)(BOOST_PP_ENUM_PARAMS_Z(1, N, T)) Q
  , Target*
)
{
    return N2O_LIST_INC(BOOST_PP_INC(N))<
        RT
      , BOOST_DEDUCED_TYPENAME most_derived<Target, ClassT>::type&
        BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, T)
    >();
}


# undef N
# undef Q

#endif // ! defined(BOOST_PP_IS_ITERATING)
#endif // BOOST_PP_IS_ITERATING
