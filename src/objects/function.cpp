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

function::function(js_function const& f) :
    f_(f)
{}

function::~function() {}

v8::Handle<v8::Value>
function::operator()(v8::FunctionCallbackInfo<v8::Value> const& args) const {
    unsigned arg_count = args.Length();
    function const* func = this;
    do {
        v8::TryCatch try_catch;
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

namespace {

struct bind {
    bind(function * f, v8::FunctionCallbackInfo<v8::Value> const& args) :
        f_(f), args_(args)
    {}

    void operator()() { (*f_)(args_); }
private:
    function * f_;
    v8::FunctionCallbackInfo<v8::Value> const& args_;
};

} // end of anonymous namespace

void
function::call(v8::FunctionCallbackInfo<v8::Value> const& args) {
    function * f = unwrap(args.Data());
    handle_exception(bind(f, args));
}

void
function::argument_error(v8::FunctionCallbackInfo<v8::Value> const& args) const {
    std::string message("javascript argument types ");
    v8::String::Utf8Value s(this->name().As<v8::String>());
    message += std::string(*s) + "(";
    int argc = args.Length();
    for (int i = 0; i < argc; ++i) {
        message += js_typeof(args[i]).name();
        if (i < argc - 1) { message += ", "; }
    }
    message += ") did not match c++ signature:\n";
    
    js_type_error(message.c_str());
    throw_error_already_set();
}

v8::Handle<v8::Value>
function::name() const {
    v8::Local<v8::Function> f = v8::Local<v8::Function>::New(v8::Isolate::GetCurrent(), self_);
    v8::Local<v8::String> name = f->GetName().As<v8::String>();
    if (name->Length() != 0) {
        return name;
    }
    return f->GetInferredName();
}

}} // end of namespace n2o::objects
