//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_MAKE_FUNCTION_INCLUDED
#define N2O_DETAIL_MAKE_FUNCTION_INCLUDED

namespace n2o { namespace detail {

template <typename F, typename CallPolicies, typename Sig>
v8::Local<v8::Function>
make_function(F f, CallPolicies const& p, Sig signature) {
    v8::Isolate * isolate = v8::Isolate::GetCurrent();
    static v8::Persistent<v8::FunctionTemplate> proto_template;
    v8::Local<v8::FunctionTemplate> pt;
    if (proto_template.IsEmpty()) {
        pt = v8::FunctionTemplate::New(isolate);
        pt->InstanceTemplate()->SetInternalFieldCount(1);
        proto_template.Reset(isolate, pt);
    } else {
        pt = v8::Local<v8::FunctionTemplate>::New(isolate, proto_template);
    }
    typedef typename detail::caller<F, CallPolicies, Sig> caller;
    v8::Local<v8::Value> c = caller::create(f, CallPolicies());
    v8::Local<v8::Function> function = v8::Function::New(isolate, caller::call, c);
    v8::Local<v8::Object> prototype = pt->GetFunction()->NewInstance();
    prototype->SetInternalField(0, c);
    v8::Local<v8::Value> original_proto = function->GetPrototype();
    function->SetPrototype(prototype);
    prototype->SetPrototype(original_proto);
    return function;
}

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_MAKE_FUNCTION_INCLUDED
