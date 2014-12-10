//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_VALUE_IS_SHARED_PTR_INCLUDED
# define N2O_DETAIL_VALUE_IS_SHARED_PTR_INCLUDED

# include <n2o/settings.hpp>

# include <boost/shared_ptr.hpp>

# include <n2o/detail/value_is_xxx.hpp>

namespace n2o { namespace detail {

N2O_VALUE_IS_XXX_DEF(shared_ptr, boost::shared_ptr, 1)

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_VALUE_IS_SHARED_PTR_INCLUDED
