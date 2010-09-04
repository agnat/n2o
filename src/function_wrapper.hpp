#ifndef N2O_FUNCTION_WRAPPER
#define N2O_FUNCTION_WRAPPER

#include "config.h"

#include <v8.h>

namespace n2o { namespace detail {

extern v8::Persistent<v8::ObjectTemplate> function_wrapper_template;

template <typename F>
v8::Local<v8::Object>
wrap_function(F native_function) {
    if (function_wrapper_template.IsEmpty()) {
        v8::Local<v8::ObjectTemplate> t = v8::ObjectTemplate::New();
        t->SetInternalFieldCount(1);
        function_wrapper_template = v8::Persistent<v8::ObjectTemplate>::New(t);
    }
    v8::Local<v8::Object> wrapped_function = function_wrapper_template->NewInstance();
    wrapped_function->SetPointerInInternalField(0, reinterpret_cast<void*>(native_function));
    return wrapped_function;
}

template <typename F>
F
unwrap_function(v8::Arguments const& args) {
    return reinterpret_cast<F>(args.Data()->ToObject()->GetPointerFromInternalField(0));
}

}} // end of namespace detail, n2o
#endif // N2O_FUNCTION_WRAPPER
