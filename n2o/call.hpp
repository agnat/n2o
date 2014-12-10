#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
# ifndef N2O_CALL_INCLUDED
#  define N2O_CALL_INCLUDED

#  include <n2o/settings.hpp>

#  include <boost/preprocessor/comma_if.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>

#  include <v8.h>

#  include <n2o/converter/arg_to_js.hpp>
#  include <n2o/converter/return_from_js.hpp>
#  include <n2o/detail/void_return.hpp>

namespace n2o {

#  define N2O_FAST_ARG_TO_JS_GET(z, n, _) \
    converter::arg_to_js<A##n>(a##n).get()

#  define BOOST_PP_ITERATION_PARAMS_1 (3, (0, N2O_MAX_ARITY, <n2o/call.hpp>))
#  include BOOST_PP_ITERATE()

#  undef N2O_FAST_ARG_TO_JS_GET

} // end of namespace n2o

# endif // N2O_CALL_INCLUDED
#else // BOOST_PP_IS_ITERATING
# if BOOST_PP_ITERATION_DEPTH() == 1
#  define N BOOST_PP_ITERATION()

template <typename R BOOST_PP_ENUM_TRAILING_PARAMS_Z(1, N, typename A)>
typename detail::returnable<R>::type
call( v8::Handle<v8::Value> callable
    , v8::Handle<v8::Value> receiver
    BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, const& a)
    , boost::type<R>* = 0)
{
    v8::Handle<v8::Value> args[N] = { BOOST_PP_ENUM(N , N2O_FAST_ARG_TO_JS_GET, nil) };
    v8::Local<v8::Value> result;
    if (callable->IsFunction()) {
        result = callable.As<v8::Function>()->Call(receiver, N, args);
    } else if (callable->IsObject()) {
        result = callable.As<v8::Object>()->CallAsFunction(receiver, N, args);
    } else {
        js_error("not a callable");
        throw_error_already_set();
    }

    converter::return_from_js<R> converter;
    return converter(result);
}

#  undef N
# endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING
