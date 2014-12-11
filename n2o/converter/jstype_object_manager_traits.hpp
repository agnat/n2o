//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_JSTYPE_OBJECT_MANAGER_TRAITS_INCLUDED
# define N2O_CONVERTER_JSTYPE_OBJECT_MANAGER_TRAITS_INCLUDED

#include <n2o/settings.hpp>

namespace n2o { namespace converter {

template <typename T> struct object_manager_traits;

template <typename JSType, typename T>
struct jstype_object_manager_traits {
    static const bool is_specialized = true;
    static inline v8::Handle<v8::Value> adopt(v8::Handle<v8::Value>);
};

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_JSTYPE_OBJECT_MANAGER_TRAITS_INCLUDED
