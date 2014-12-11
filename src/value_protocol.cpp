//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================

#include <n2o/value_protocol.hpp>

namespace n2o { namespace api {

value
getproperty(value const& target, value const& key) {
    return value(target.handle().As<v8::Object>()->Get(key.handle()));
}

void
setproperty(value const& target, value const& key, value const& v) {
    target.handle().As<v8::Object>()->Set(key.handle(), v.handle());
}

void
delproperty(value const& target, value const& key) {
    target.handle().As<v8::Object>()->Delete(key.handle().As<v8::String>());
}

}} // end of namespace api
