//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_ARG_TO_JS_BASE_INCLUDED
# define N2O_CONVERTER_ARG_TO_JS_BASE_INCLUDED

# include <n2o/settings.hpp>

# include <v8.h>

namespace n2o { namespace converter {

struct registration;

namespace detail {

struct arg_to_js_base {
    arg_to_js_base(void const volatile* source, registration const&);
    v8::Handle<v8::Value> get() const { return v8::Local<v8::Value>::New(v8::Isolate::GetCurrent(), ptr_); }
    v8::Handle<v8::Value> release() {
        v8::Local<v8::Value> v = v8::Local<v8::Value>::New(v8::Isolate::GetCurrent(), ptr_);
        ptr_.Reset();
        return v;
    }
private:
    v8::Persistent<v8::Value> ptr_;
};

} // end of namespace detail

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_ARG_TO_JS_BASE_INCLUDED
