#ifndef N2O_FUNCTION_INCLUDED
#define N2O_FUNCTION_INCLUDED

#include "config.h"

#include "function_wrapper.hpp"

#include "caller.hpp"
#include "context_stack.hpp"

namespace n2o {

namespace detail {

template <typename F, typename Sig>
v8::Local<v8::FunctionTemplate>
make_function(F f, Sig signature) {
    return v8::FunctionTemplate::New( detail::caller<F, Sig>::call,
            detail::caller<F, Sig>::create(f));
}

} // end of namespace detail

template <typename F>
void
function(const char * name, F f) {
    
    v8::Local<v8::FunctionTemplate> t = detail::make_function(f, detail::get_signature(f));
    detail::get_context()->Set( v8::String::NewSymbol(name), t->GetFunction());
}

} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
