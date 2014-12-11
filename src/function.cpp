//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o/function.hpp>

namespace n2o {

namespace detail {

function_base::function_base() : value() {}

function_base::function_base(value_cref arg) : value(arg) {}

}

} // end of namespace n2o 
