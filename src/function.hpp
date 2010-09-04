#ifndef N2O_FUNCTION_INCLUDED
#define N2O_FUNCTION_INCLUDED

#include "config.h"

#include "function_wrapper.hpp"

#include "caller.hpp"
#include "context_stack.hpp"

namespace n2o {

template <typename F>
void
function(const char * name, F f) {
    v8::Local<v8::Value> data = detail::wrap_function(f);
    detail::get_context()->Set(v8::String::NewSymbol(name),
            v8::FunctionTemplate::New(detail::caller<F>::call, data)->GetFunction());
}

} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
