//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIÖ_PROPERTY_VALUE_INCLUDED
#define N2O_DETAIÖ_PROPERTY_VALUE_INCLUDED

#include <n2o/function.hpp>
#include <n2o/constructor.hpp>

namespace n2o { namespace detail {

struct property_value {
  property_value(v8::Handle<v8::Object> o, const char * name) : obj_(o), name_(name) {}

  v8::Local<v8::Object> obj_;
  const char *          name_;

  property_value operator=(function const& v) {
    obj_->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name_), v.js_function());
    return *this;
  }
  template <typename T>
  property_value operator=(constructor<T> const& v) {
    obj_->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name_), v.function_template()->GetFunction());
    return *this;
  }
};


}} // end of namespace n2o::detail
#endif // N2O_DETAIÖ_PROPERTY_VALUE_INCLUDED
