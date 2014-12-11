//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_FUNCTION_INCLUDED
# define N2O_FUNCTION_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/default_call_policies.hpp>
# include <n2o/detail/caller.hpp>
# include <n2o/detail/make_function.hpp>
# include <n2o/converter/jstype_object_manager_traits.hpp>
# include <n2o/value.hpp>
# include <n2o/signature.hpp>

namespace n2o {

namespace detail {

struct function_base : value {
protected:
    function_base();
    explicit function_base(value_cref rhs);
};

} // end of namespace detail

class function : public detail::function_base {
public:
    template <typename F>
    explicit function(F f) 
        : detail::function_base(value(
                     detail::make_function( f
                                          , default_call_policies()
                                          , detail::get_signature(f))))
    {}

    template <typename F>
    function(char const* name, F f)
        : detail::function_base(value(
                     detail::make_function( f
                                          , default_call_policies()
                                          , detail::get_signature(f))))
    {
        handle().As<v8::Function>()->SetName(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name));
    }


    template <typename F>
    function &
    add_overload(F f) {
        return *this;
    }
};

namespace converter {
    template <>
    struct object_manager_traits<function>
        : jstype_object_manager_traits<v8::Function, function>
    {};
} // end of namespace converter
} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
