#ifndef N2O_DETAIL_MAKE_FUNCTION_INCLUDED
#define N2O_DETAIL_MAKE_FUNCTION_INCLUDED

namespace n2o { namespace detail {

template <typename F, typename CallPolicies, typename Sig>
v8::Local<v8::FunctionTemplate>
make_function(F f, CallPolicies const& p, Sig signature) {
    typedef typename detail::caller<F, CallPolicies, Sig> caller;
    return v8::FunctionTemplate::New(
              v8::Isolate::GetCurrent()
            , caller::call
            , caller::create(f, CallPolicies())
            );
}

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_MAKE_FUNCTION_INCLUDED
