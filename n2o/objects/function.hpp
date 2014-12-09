//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_OBJECTS_FUNCTION_INCLUDED
# define N2O_OBJECTS_FUNCTION_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/objects/js_function.hpp>

namespace n2o { namespace objects {

class function {
public:
    function(js_function const& f);
    ~function();

    static
    void
    call(v8::FunctionCallbackInfo<v8::Value> const& args);
    v8::Handle<v8::Value>
    operator()(v8::FunctionCallbackInfo<v8::Value> const& args) const;

    v8::Handle<v8::Value> name() const;

    static inline
    v8::Handle<v8::Value>
    create(js_function const& f) {
        return v8::External::New(v8::Isolate::GetCurrent(), new function(f));
    }

    static inline
    void
    set_self(v8::Handle<v8::Value> f, v8::Handle<v8::Function> jsf) {
        function * func = unwrap(f);
        func->self_.Reset(v8::Isolate::GetCurrent(), jsf);
        // TODO: func->self.SetWeak()
    }
private:
    v8::Handle<v8::Value> signature(bool show_return_type = false) const;
    v8::Handle<v8::Value> signatures(bool show_return_type = false) const;
    void argument_error(v8::FunctionCallbackInfo<v8::Value> const& args) const;
    void add_overload(function const& f);

    static inline function * unwrap(v8::Handle<v8::Value> value) {
        return value.IsEmpty()
            ? 0
            : reinterpret_cast<function*>(value.As<v8::External>()->Value());
    }
private:
    js_function f_;
    v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> > overloads_;
    v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Value> > self_;
};

}} // end of namespace n2o::objects

#endif // N2O_OBJECTS_FUNCTION_INCLUDED
