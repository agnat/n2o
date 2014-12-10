//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_COPY_CTOR_MUTATES_RHS_INCLUDED
# define N2O_DETAIL_COPY_CTOR_MUTATES_RHS_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/detail/is_auto_ptr.hpp>

namespace n2o { namespace detail {

template <typename T>
struct copy_ctor_mutates_rhs : is_auto_ptr<T> {};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_COPY_CTOR_MUTATES_RHS_INCLUDED
