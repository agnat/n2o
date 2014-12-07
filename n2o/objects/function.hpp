//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_OBJECTS_FUNCTION_INCLUDED
# define N2O_OBJECTS_FUNCTION_INCLUDED

#include <n2o/objects/js_function.hpp>

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

private:
    v8::Handle<v8::Value> signature(bool show_return_type = false) const;
    v8::Handle<v8::Value> signatures(bool show_return_type = false) const;
    void argument_error(v8::FunctionCallbackInfo<v8::Value> const& args) const;
    void add_overload(function const& f);

    static inline function * unwrap(v8::Handle<v8::Value> value) {
        return value.IsEmpty() ? 0 : reinterpret_cast<function*>(value.As<v8::External>()->Value());
    }
private:
    js_function f_;
    v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value> > overloads_;
};

}} // end of namespace n2o::objects

#endif // N2O_OBJECTS_FUNCTION_INCLUDED
