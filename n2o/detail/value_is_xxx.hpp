//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_VALUE_IS_XXX_INCLUDED
# define N2O_DETAIL_VALUE_IS_XXX_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/bool.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/remove_cv.hpp>

# include <n2o/detail/is_xxx.hpp>

# define N2O_VALUE_IS_XXX_DEF(name, qualified_name, nargs)      \
template <typename X_>                                          \
struct value_is_##name {                                        \
    N2O_IS_XXX_DEF(name, qualified_name, nargs)                 \
    static const bool value = is_##name<                        \
        typename boost::remove_cv<                              \
            typename boost::remove_reference<X_>::type          \
        >::type                                                 \
    >::value;                                                   \
    typedef boost::mpl::bool_<value> type;                      \
};

#endif // N2O_DETAIL_VALUE_IS_XXX_INCLUDED
