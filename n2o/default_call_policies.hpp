//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DEFAULT_CALL_POLICIES_INCLUDED
# define N2O_DEFAULT_CALL_POLICIES_INCLUDED

# include <iostream>

# include <boost/mpl/if.hpp>
# include <boost/mpl/or.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_reference.hpp>

# include <n2o/to_js_value.hpp>

namespace n2o {

namespace detail {
  template <class T> struct specifiy_a_return_value_policy_to_wrap_functions_returning {};
}

struct default_result_converter {
    template <typename R>
    struct apply {
        typedef typename boost::mpl::if_<
           boost::mpl::or_<boost::is_pointer<R>, boost::is_reference<R> >,
           detail::specifiy_a_return_value_policy_to_wrap_functions_returning<R>,
           n2o::to_js_value< typename detail::value_arg<R>::type >
        >::type type;
    };
};

struct default_call_policies {
    template <typename ArgumentPackage>
    static
    bool
    precall(ArgumentPackage const&) {
        return true;
    }
    template <typename ArgumentPackage>
    static
    void
    postcall(ArgumentPackage const& args, v8::Handle<v8::Value> result) {
        args.GetReturnValue().Set(result);
    }
    typedef default_result_converter result_converter;
};

template <>
struct default_result_converter::apply<char const*> {
    typedef to_js_value<char const* const&> type;
};

} // end of namespace n2o

#endif // N2O_DEFAULT_CALL_POLICIES_INCLUDED
