//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_TO_JS_FUNCTION_TYPE_INCLUDED
# define N2O_CONVERTER_TO_JS_FUNCTION_TYPE_INCLUDED

# include <n2o/settings.hpp>

# include <v8.h>

namespace n2o { namespace converter {

typedef v8::Handle<v8::Value> (*to_js_function_t)(void const*);

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_TO_JS_FUNCTION_TYPE_INCLUDED
