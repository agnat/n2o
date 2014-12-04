//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_OBJECT_INCLUDED
#define N2O_OBJECT_INCLUDED

#include <n2o/detail/property_value.hpp>

namespace n2o {

class object {
  public:
    explicit object(v8::Handle<v8::Object> o) : obj_(o) {}

    detail::property_value operator[](const char * name) {
      return detail::property_value(obj_, name);
    }

    v8::Local<v8::Object> obj_;
};

}

#endif // N2O_OBJECT_INCLUDED
