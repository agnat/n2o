//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================

#include <n2o/objects/function.hpp>

#include <sstream>

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

v8::Handle<v8::Value>
function::signature(bool show_return_type) const {
    js_function const& impl = f_;

    detail::signature_element const* return_type = impl.signature();
    detail::signature_element const* s = return_type + 1;

    v8::Isolate * isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Array> formal_parameters = v8::Array::New(isolate);
    if (impl.max_arity() == 0) {
        formal_parameters->Set(0, v8::String::NewFromUtf8(isolate, "void"));
    }

    for (unsigned i = 0; i < impl.max_arity(); ++i) {
        if (s[i].basename == 0) {
            formal_parameters->Set(i, v8::String::NewFromUtf8(isolate,"..."));
            break;
        }

        v8::Local<v8::String> parameter = v8::String::NewFromUtf8(isolate, s[i].basename);
        if (s[i].lvalue) {
            parameter = v8::String::Concat( parameter
                                          , v8::String::NewFromUtf8(isolate, " {lvalue}"));
        }
        formal_parameters->Set(i, parameter);
    }

    std::ostringstream sig;
    v8::String::Utf8Value name(this->name().As<v8::String>());
    sig << *name << "(";
    unsigned argc = formal_parameters->Length();
    for (unsigned i = 0; i < argc; ++i) {
        v8::String::Utf8Value param(formal_parameters->Get(i).As<v8::String>());
        sig << *param;
        if (i < argc - 1) {
            sig << ", ";
        }
    }
    sig << ")";
    if (show_return_type) {
        sig << " -> " << return_type->basename;
    }
    return v8::String::NewFromUtf8(isolate, sig.str().c_str());
}

v8::Handle<v8::Value>
function::signatures(bool show_return_type) const {
    v8::Isolate * isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Array> result = v8::Array::New(isolate);
    unsigned i = 0;
    for (function const* f = this; f; f = unwrap(v8::Local<v8::Value>::New(isolate, f->overloads_))) {
        result->Set(i++, f->signature(show_return_type));
    }
    return result;
}

void
function::argument_error(v8::FunctionCallbackInfo<v8::Value> const& args) const {
    std::ostringstream msg;
    v8::String::Utf8Value s(this->name().As<v8::String>());
    msg << "javascript argument types " << *s << "(";
    int argc = args.Length();
    for (int i = 0; i < argc; ++i) {
        msg << js_typeof(args[i]).name();
        if (i < argc - 1) { msg << ", "; }
    }
    msg << ") did not match c++ signature:\n";

    v8::Local<v8::Array> sigs = signatures().As<v8::Array>();
    unsigned sig_count = sigs->Length();
    for (unsigned i = 0; i < sig_count; ++i) {
        v8::String::Utf8Value sig(sigs->Get(i).As<v8::String>());
        msg << "" << *sig;
        if (i < sig_count - 1) {
            msg << "\n";
        }
    }
    
    js_type_error(msg.str().c_str());
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
