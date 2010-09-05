#ifndef N2O_DEFAULT_CALL_POLICIES_INCLUDED
#define N2O_DEFAULT_CALL_POLICIES_INCLUDED

#include <iostream>

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>

#include "to_v8_value.hpp"

namespace n2o {

namespace detail {
  template <class T> struct specifiy_a_return_value_policy_to_wrap_functions_returning {};
}

struct dummy_result_converter {
    template <typename T>
    v8::Handle<v8::Value>
    operator()(T v) const {
        std::cout << "result converter()" << std::endl;
    }
};

struct default_result_converter {
    template <typename R>
    struct apply {
        //typedef dummy_result_converter type;
        typedef typename boost::mpl::if_<
           boost:: mpl::or_<boost::is_pointer<R>, boost::is_reference<R> >,
           detail::specifiy_a_return_value_policy_to_wrap_functions_returning<R>,
           n2o::to_v8_value< typename detail::value_arg<R>::type >
        >::type type;
    };
};

struct default_call_policies {
    typedef default_result_converter result_converter;
};

}

#endif // N2O_DEFAULT_CALL_POLICIES_INCLUDED
