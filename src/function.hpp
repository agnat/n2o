#ifndef N2O_FUNCTION_INCLUDED
#define N2O_FUNCTION_INCLUDED

#include "config.h"

#include "default_call_policies.hpp"

#include "caller.hpp"

namespace n2o {

namespace detail {

// XXX duplicate
template <typename F, typename CallPolicies, typename Sig>
v8::Local<v8::FunctionTemplate>
make_function(F f, CallPolicies const& p, Sig signature) {
    typedef detail::caller<F, CallPolicies, Sig> caller;
    return v8::FunctionTemplate::New(
              v8::Isolate::GetCurrent()
            , caller::call
            , caller::create(f, CallPolicies())
            );
}

} // end of namespace detail

template <typename F>
v8::Local<v8::FunctionTemplate>
function(F f) {
    return detail::make_function(
            f, default_call_policies(), detail::get_signature(f));
}

} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
