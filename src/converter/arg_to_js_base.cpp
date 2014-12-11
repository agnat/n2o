//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================

#include <n2o/converter/arg_to_js_base.hpp>

#include <n2o/converter/registrations.hpp>

namespace n2o { namespace converter { namespace detail {

arg_to_js_base::arg_to_js_base(void const volatile* src, registration const& converters)
    : ptr_(v8::Isolate::GetCurrent(), converters.to_js(src))
{}

}}} // end of namespace n2o::converter::detail
