#ifndef N2O_FUNCTION_INCLUDED
#define N2O_FUNCTION_INCLUDED

#include "config.h"

#include "default_call_policies.hpp"

#include "caller.hpp"
#include "context_stack.hpp"

namespace n2o {

namespace detail {

// XXX duplicate
template <typename F, typename CallPolicies, typename Sig>
v8::Local<v8::FunctionTemplate>
make_function(F f, CallPolicies const& p, Sig signature) {
    typedef detail::caller<F, CallPolicies, Sig> caller;
    return v8::FunctionTemplate::New( caller::call,
            caller::create(f, CallPolicies()));
}

} // end of namespace detail

template <typename F>
void
function(const char * name, F f) {
    
    v8::Local<v8::FunctionTemplate> t = detail::make_function(
            f, default_call_policies(), detail::get_signature(f));
    detail::get_context()->Set( v8::String::NewSymbol(name), t->GetFunction());
}

} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
