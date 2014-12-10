//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_PROPERTY_VALUE_INCLUDED
# define N2O_DETAIL_PROPERTY_VALUE_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/function.hpp>
# include <n2o/constructor.hpp>

namespace n2o { namespace detail {

struct property_value {
    property_value(v8::Handle<v8::Object> o, const char * name) : obj_(o), name_(name) {}

    v8::Local<v8::Object> obj_;
    const char *          name_;

    property_value operator=(v8::Handle<v8::Value> v) {
        obj_->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name_), v);
        return *this;
    }
    property_value operator=(function const& v) {
        v8::Isolate * isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Function> f = v.js_function();
        /*
        v8::Local<v8::String> name = f->GetName().As<v8::String>();
        if (name->Length() == 0) {
            f->SetName(v8::String::NewFromUtf8(isolate, name_));
        }
        */
        obj_->Set(v8::String::NewFromUtf8(isolate, name_), f);
        return *this;
    }
    template <typename T>
        property_value operator=(constructor<T> const& v) {
            obj_->Set( v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name_)
                     , v.function_template()->GetFunction());
            return *this;
        }
};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_PROPERTY_VALUE_INCLUDED
