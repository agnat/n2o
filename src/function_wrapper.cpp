#include "function_wrapper.hpp"

namespace n2o { namespace detail {

static v8::Persistent<v8::ObjectTemplate> function_wrapper_template;

v8::Local<v8::Object>
get_function_wrapper(void * native_function) {
    if (function_wrapper_template.IsEmpty()) {
        v8::Local<v8::ObjectTemplate> t = v8::ObjectTemplate::New();
        t->SetInternalFieldCount(1);
        function_wrapper_template = v8::Persistent<v8::ObjectTemplate>::New(t);
    }
    v8::Local<v8::Object> wrapped_function = function_wrapper_template->NewInstance();
    wrapped_function->SetPointerInInternalField(0, native_function);
    return wrapped_function;
}


}}

