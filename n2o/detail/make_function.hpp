//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_MAKE_FUNCTION_INCLUDED
# define N2O_DETAIL_MAKE_FUNCTION_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/objects/js_function.hpp>
# include <n2o/objects/function.hpp>
# include <n2o/detail/caller.hpp>

namespace n2o { namespace detail {

template <typename F, typename CallPolicies, typename Sig>
v8::Handle<v8::Function>
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
    caller c(f, CallPolicies());
    objects::js_function js_func(c, Sig());
    v8::Local<v8::Value> func = objects::function::create(js_func);
    v8::Local<v8::Function> function = v8::Function::New(isolate, objects::function::call, func);
    objects::function::set_self(func, function);
    v8::Local<v8::Object> prototype = pt->GetFunction()->NewInstance();
    prototype->SetInternalField(0, func);
    v8::Local<v8::Value> original_proto = function->GetPrototype();
    function->SetPrototype(prototype);
    prototype->SetPrototype(original_proto);
    return function;
}

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_MAKE_FUNCTION_INCLUDED
