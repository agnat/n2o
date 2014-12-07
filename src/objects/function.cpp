//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================

#include <n2o/objects/function.hpp>

#include <boost/bind.hpp>

#include <n2o/errors.hpp>

namespace n2o { namespace objects {

js_function_impl_base::~js_function_impl_base() {}

unsigned
js_function_impl_base::max_arity() const { return this->min_arity(); }

function::function(js_function const& f) : f_(f) {}
function::~function() {}

v8::Handle<v8::Value>
function::operator()(v8::FunctionCallbackInfo<v8::Value> const& args) const {
    v8::TryCatch try_catch;
    unsigned arg_count = args.Length();
    function const* func = unwrap(args.Data());
    do {
        unsigned min_arity = func->f_.min_arity();
        unsigned max_arity = func->f_.max_arity();
        if (arg_count >= min_arity && arg_count <= max_arity) {
        
            v8::Handle<v8::Value> result = func->f_(args);
            if (try_catch.HasCaught()) {
                try_catch.ReThrow();
                return result;
            } else if (not result.IsEmpty()) {
                return result;
            }
        }

        func = unwrap(v8::Local<v8::Value>::New(args.GetIsolate(), func->overloads_));
    } while (func);

    argument_error(args);
    return v8::Handle<v8::Value>();
}

void
function::call(v8::FunctionCallbackInfo<v8::Value> const& args) {
    function * f = unwrap(args.Data());
    handle_exception(boost::bind<void>(*f, args));
}

}} // end of namespace n2o::objects
