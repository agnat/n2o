#ifndef N2O_DETAIL_MAKE_FUNCTION_INCLUDED
#define N2O_DETAIL_MAKE_FUNCTION_INCLUDED

namespace n2o { namespace detail {

template <typename F, typename CallPolicies, typename Sig>
v8::Local<v8::Function>
make_function(F f, CallPolicies const& p, Sig signature) {
    static v8::Persistent<v8::FunctionTemplate> proto_template;
    v8::Local<v8::FunctionTemplate> pt;
    if (proto_template.IsEmpty()) {
        pt = v8::FunctionTemplate::New(v8::Isolate::GetCurrent());
        pt->InstanceTemplate()->SetInternalFieldCount(1);
        proto_template.Reset(v8::Isolate::GetCurrent(), pt);
    } else {
        pt = v8::Local<v8::FunctionTemplate>::New(v8::Isolate::GetCurrent(), proto_template);
    }
    typedef typename detail::caller<F, CallPolicies, Sig> caller;
    v8::Local<v8::Value> c = caller::create(f, CallPolicies());
    v8::Local<v8::Function> function = v8::Function::New(v8::Isolate::GetCurrent(), caller::call, c);
    v8::Local<v8::Object> prototype = pt->GetFunction()->NewInstance();
    prototype->SetInternalField(0, c);
    v8::Local<v8::Value> original_proto = function->GetPrototype();
    function->SetPrototype(prototype);
    prototype->SetPrototype(original_proto);
    return function;
}

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_MAKE_FUNCTION_INCLUDED
