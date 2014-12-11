//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_VALUE_PROPERTIES_INCLUDED
# define N2O_VALUE_PROPERTIES_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/proxy.hpp>
# include <n2o/value_core.hpp>
# include <n2o/value_protocol.hpp>

namespace n2o { namespace api {

struct const_property_policies {
    typedef value key_type;
    static value get(value const& target, value const& key);
};

struct property_policies : const_property_policies {
    static value const& set(value const& target, value const& key, value const& v);
    static void del(value const& target, value const& key);
};

//=== Implementation ===========================================================

template <typename U>
inline
value_property
value_operators<U>::operator[](value_cref key) {
    value_cref x = *static_cast<U*>(this);
    return value_property(x, key);
}

template <typename U>
inline
const_value_property
value_operators<U>::operator[](value_cref key) const {
    value_cref x = *static_cast<U const*>(this);
    return const_value_property(x, key);
}

template <typename U>
template <typename T>
inline
value_property
value_operators<U>::operator[](T const& key) {
    return (*this)[value(key)];
}

inline
value
const_property_policies::get(value const& target, value const& key) {
    return getproperty(target, key);
}

inline
value const&
property_policies::set(value const& target, value const& key, value const& v) {
    setproperty(target, key, v);
    return v;
}

inline
void
property_policies::del(value const& target, value const& key) {
    delproperty(target, key);
}

}} // end of namespace n2o::api

#endif // N2O_VALUE_PROPERTIES_INCLUDED
