//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_VALUE_PROTOCOL_INCLUDED
# define N2O_VALUE_PROTOCOL_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/value_protocol_core.hpp>
# include <n2o/value_core.hpp>

namespace n2o { namespace api {

template <typename Target, typename Key>
value
getproperty(Target const& target, Key const& key) {
    return getproperty(value(target), value(key));
}

template <typename Key, typename Value>
void
setproperty(value const& target, Key const& key, Value const& v) {
    setproperty(target, value(key), value(v));
}

template <typename Key>
void
delproperty(value const& target, Key const& key) {
    delproperty(target, value(key));
}

}} // end of namespace n2o

#endif // N2O_VALUE_PROTOCOL_INCLUDED
