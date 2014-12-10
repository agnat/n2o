//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_FROM_JS_INCLUDED
# define N2O_CONVERTER_FROM_JS_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/converter/rvalue_from_js_data.hpp>
# include <n2o/converter/convertible_function.hpp>
# include <n2o/converter/registrations.hpp>
# include <n2o/converter/rvalue_from_js_data.hpp>

namespace n2o { namespace converter {

rvalue_from_js_stage1_data
rvalue_from_js_stage1(v8::Handle<v8::Value>, registration const&);

void * rvalue_result_from_js(v8::Handle<v8::Value>, rvalue_from_js_stage1_data&);

void * reference_result_from_js(v8::Handle<v8::Value>, registration const&);
void * pointer_result_from_js(v8::Handle<v8::Value>, registration const&);

void void_result_from_js(v8::Handle<v8::Value>);


}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_FROM_JS_INCLUDED
