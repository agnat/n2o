#ifndef N2O_FUNCTION_WRAPPER_INCLUDED
#define N2O_FUNCTION_WRAPPER_INCLUDED

#include <iostream>

namespace n2o { namespace detail {

template <typename F>
struct caller {
    static
    v8::Handle<v8::Value>
    call(v8::Arguments const& args) {
        HandleScope scope;
        v8::Local<v8::Object> data = args.Data()->ToObject();
        F f(reinterpret_cast<F>(data->GetPointerFromInternalField(0)));
        f();
    }
};

}} // end of namespace detail, n2o

#endif // N2O_FUNCTION_WRAPPER_INCLUDED
