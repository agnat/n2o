//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_FUNCTION_INCLUDED
# define N2O_FUNCTION_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/default_call_policies.hpp>
# include <n2o/detail/caller.hpp>
# include <n2o/detail/make_function.hpp>
# include <n2o/value_core.hpp>
# include <n2o/signature.hpp>

namespace n2o {

class function /* : TODO: public object */ {
public:
    template <typename F>
    explicit function(F f) :
        v8_function_(detail::make_function( f
                                          , default_call_policies()
                                          , detail::get_signature(f)))
    {}

    template <typename F>
    function(char const* name, F f) : // C++11: function(f) {
        v8_function_(detail::make_function( f
                                          , default_call_policies()
                                          , detail::get_signature(f)))
    {
        v8_function_->SetName(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name));
    }


    template <typename F>
    function &
    add_overload(F f) {
        return *this;
    }


    v8::Handle<v8::Function>
    js_function() const { return v8_function_; }

private:
    v8::Local<v8::Function> v8_function_;
};

} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
