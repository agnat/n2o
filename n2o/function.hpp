#ifndef N2O_FUNCTION_INCLUDED
#define N2O_FUNCTION_INCLUDED

#include <n2o/config.h>

#include <n2o/default_call_policies.hpp>
#include <n2o/detail/caller.hpp>
#include <n2o/detail/make_function.hpp>
#include <n2o/objects/object_base.hpp>

namespace n2o {

class function /*: public object */ {
public:
    template <typename F>
    explicit
    function(F f) :
        js_function_(detail::make_function( f
                                       , default_call_policies()
                                       , detail::get_signature(f)))
    {} 

    template <typename F>
    explicit
    function(char const* name, F f) : // C++11: function(f) {
        js_function_(detail::make_function( f
                                       , default_call_policies()
                                       , detail::get_signature(f)))
    {
        js_function_->SetName(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name));
    } 


    v8::Handle<v8::Function>
    js_function() const { return js_function_; }
private:
    v8::Local<v8::Function> js_function_;
};

} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
