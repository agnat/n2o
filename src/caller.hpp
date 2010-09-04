#ifndef N2O_FUNCTION_WRAPPER_INCLUDED
#define N2O_FUNCTION_WRAPPER_INCLUDED

#include "config.h"

#include <iostream>

#include "function_wrapper.hpp"

namespace n2o { namespace detail {

template <typename F>
struct caller {
    static
    v8::Handle<v8::Value>
    call(v8::Arguments const& args) {
        v8::HandleScope scope;
        F f(detail::unwrap_function<F>(args));
        f();
        return v8::Undefined();
    }
};

}} // end of namespace detail, n2o

#endif // N2O_FUNCTION_WRAPPER_INCLUDED
