//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================

#include <n2o/object.hpp>

namespace n2o { namespace detail {

object_base::object_base(value_cref other) : value(other) {}

}} // end of namespace n2o::detail
