//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef BOOST_PP_IS_ITERATING
# error N2O - do not include this file
# include <n2o/settings.hpp>
#endif

#define N BOOST_PP_ITERATION()

template <BOOST_PP_ENUM_PARAMS_Z(1, N, class A)>
typename detail::dependent<value, A0>::type
operator()(BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, const& a)) const {
    typedef typename detail::dependent<value, A0>::type val;
    U const& self = *static_cast<U const*>(this);
    return call<val>(get_managed_object(self, tag), BOOST_PP_ENUM_PARAMS_Z(1, N, a));
}

#undef N
