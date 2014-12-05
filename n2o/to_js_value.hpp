//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_TO_JS_VALUE_INCLUDED
# define N2O_TO_JS_VALUE_INCLUDED

# include <n2o/value_arg.hpp>
# include <n2o/converter/builtin_converters.hpp>

namespace n2o {

namespace detail {

template <typename T>
struct registry_to_js_value {
    typedef typename detail::value_arg<T>::type argument_type;

    v8::Handle<v8::Value> operator()(argument_type) const;
};

} // end of namespace detail

template <typename T>
struct to_js_value : detail::registry_to_js_value<T> {};


namespace detail {

template <typename T>
inline
v8::Handle<v8::Value>
registry_to_js_value<T>::operator()(argument_type x) const {
    return v8::Undefined(v8::Isolate::GetCurrent());
}

} // end of namespace detail

} // end of namespace n2o

#endif // N2O_TO_JS_VALUE_INCLUDED
