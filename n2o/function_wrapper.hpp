//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_FUNCTION_WRAPPER_INCLUDED
# define N2O_FUNCTION_WRAPPER_INCLUDED

# include <n2o/settings.hpp>

# include <v8.h>

namespace n2o { namespace detail {

extern v8::Persistent<v8::ObjectTemplate> function_wrapper_template;

}} // end of namespace detail, n2o

#endif // N2O_FUNCTION_WRAPPER_INCLUDED
