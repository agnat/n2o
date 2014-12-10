//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_IS_XXX_INCLUDED
# define N2O_DETAIL_IS_XXX_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/bool.hpp>
# include <boost/preprocessor/enum_params.hpp>

# define N2O_IS_XXX_DEF(name, qualified_name, nargs)      \
template <typename T>                                     \
struct is_##name : boost::mpl::false_ {};                 \
                                                          \
template <BOOST_PP_ENUM_PARAMS_Z(1, nargs, class T)>      \
struct is_##name<                                         \
    qualified_name<BOOST_PP_ENUM_PARAMS_Z(1, nargs, T)>   \
> : boost::mpl::true_ {};

#endif // N2O_DETAIL_IS_XXX_INCLUDED
