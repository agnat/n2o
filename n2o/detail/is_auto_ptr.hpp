//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_IS_AUTO_PTR_INCLUDED
# define N2O_DETAIL_IS_AUTO_PTR_INCLUDED

# include <n2o/settings.hpp>

# include <memory>

# include <n2o/detail/is_xxx.hpp>

namespace n2o { namespace detail {

N2O_IS_XXX_DEF(auto_ptr, std::auto_ptr, 1)

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_IS_AUTO_PTR_INCLUDED
