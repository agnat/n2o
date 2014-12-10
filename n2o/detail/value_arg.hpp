//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_VALUE_ARG_INCLUDED
# define N2O_DETAIL_VALUE_ARG_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/if.hpp>
# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/add_const.hpp>

# include <n2o/detail/copy_ctor_mutates_rhs.hpp>

namespace n2o { namespace detail {


template <typename T>
struct value_arg
    : boost::mpl::if_<
          copy_ctor_mutates_rhs<T>
        , T
        , typename boost::add_reference<
            typename boost::add_const<T>::type
        >::type
    >
{};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_VALUE_ARG_INCLUDED
