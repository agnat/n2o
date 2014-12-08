#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
# ifndef N2O_CALLER_INCLUDED
#  define N2O_CALLER_INCLUDED

#  include <n2o/config.h>

#  include <boost/compressed_pair.hpp>
#  include <boost/type_traits/is_same.hpp>
#  include <boost/mpl/identity.hpp>
#  include <boost/mpl/apply.hpp>
#  include <boost/mpl/at.hpp>
#  include <boost/mpl/next.hpp>
#  include <boost/mpl/size.hpp>
#  include <boost/bind.hpp>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/dec.hpp>
#  include <boost/preprocessor/if.hpp>
#  include <boost/preprocessor/iteration/local.hpp>

#  include <iostream>

#  include <v8.h>

#  include <n2o/function_wrapper.hpp>
#  include <n2o/arg_from_js.hpp>
//#  include <n2o/errors.hpp>
#  include <n2o/detail/signature.hpp>

namespace n2o { namespace detail {

typedef int void_result_to_js;

template <typename Policies, typename Result>
struct select_result_converter :
    boost::mpl::eval_if<
        boost::is_same<Result, void>,
        boost::mpl::identity<void_result_to_js>,
        boost::mpl::apply1<typename Policies::result_converter, Result>
    >
{};

template <unsigned> struct caller_arity;

template <typename F, typename CallPolicies, typename Sig>
struct caller;

#  define N2O_NEXT(init, name, n)                                                              \
    typedef BOOST_PP_IF( n                                                                     \
                       , typename boost::mpl::next<BOOST_PP_CAT(name, BOOST_PP_DEC(n)) >::type \
                       , init) name##n;

#  define N2O_ARG_CONVERTER(n)                                    \
    N2O_NEXT(typename boost::mpl::next<first>::type, arg_iter, n) \
    typedef arg_from_js<typename arg_iter##n::type> c_t##n;       \
    c_t##n c##n(args[n]);                                         \
    if ( not c##n.convertible()) {                                \
        return v8::Handle<v8::Value>();                           \
    }


#  define BOOST_PP_ITERATION_PARAMS_1 \
        (3, (0, N2O_MAX_ARITY + 1, <n2o/detail/caller.hpp>))
#  include BOOST_PP_ITERATE()

#  undef N2O_ARG_CONVERTER
#  undef N2O_NEXT

template <typename F, typename CallPolicies, typename Sig>
struct caller_base_select {
    enum { arity = boost::mpl::size<Sig>::value - 1 };
    typedef typename caller_arity<arity>::template impl<F,CallPolicies,Sig> type;
};

template <typename F, typename CallPolicies, typename Sig>
struct caller : caller_base_select<F, CallPolicies, Sig>::type {
public:
    caller(F f, CallPolicies p) : base(f, p) {}

    /*
    static
    v8::Handle<v8::Value>
    create(F f, CallPolicies p) {
        return v8::External::New(v8::Isolate::GetCurrent(), new caller(f, p));
    }

    static
    void
    call(v8::FunctionCallbackInfo<v8::Value> const& args) {
        caller * f = reinterpret_cast<caller*>(args.Data().As<v8::External>()->Value());
        handle_exception(boost::bind<void>(*f, args));
    }
    */

private:
    typedef typename caller_base_select<F, CallPolicies, Sig>::type base;

    caller();
};

}} // end of namespace detail, n2o

# endif // N2O_CALLER_INCLUDED

#else // !defined(BOOST_PP_IS_ITERATING)

# define N BOOST_PP_ITERATION()

template <>
struct caller_arity<N> {
    template <typename F, typename Policies, typename Sig>
    struct impl {
        impl(F f, Policies p) : data_(f,p) {}

        v8::Handle<v8::Value>
        operator()(v8::FunctionCallbackInfo<v8::Value> const& args) {
            v8::HandleScope scope(v8::Isolate::GetCurrent());
            typedef typename boost::mpl::begin<Sig>::type first;
            typedef typename first::type result_t;
            typedef typename select_result_converter<Policies,result_t>::type result_converter;

            //argument_package inner_args(args);
# if N
#  define BOOST_PP_LOCAL_MACRO(i) N2O_ARG_CONVERTER(i)
#  define BOOST_PP_LOCAL_LIMITS (0, N-1)
#  include BOOST_PP_LOCAL_ITERATE()
# endif

            if (not data_.second().precall(args /*inner_args*/)) {
                return v8::Handle<v8::Value>(); // empty handle indicates mismatch
            }

            v8::Handle<v8::Value> result = detail::invoke(
                    detail::invoke_tag<result_t, F>(),
                    result_converter(),
                    data_.first()
                    BOOST_PP_ENUM_TRAILING_PARAMS(N, c));

            data_.second().postcall(args /*inner_args*/, result);
            return result;
        }

        static unsigned min_arity() { return N; }

        static
        js_function_signature_info signature() {
            const signature_element * sig = detail::signature<Sig>::elements();
            typedef typename Policies::template extract_return_type<Sig>::type rtype;
            typedef typename select_result_converter<Policies, rtype>::type result_converter;

            static const signature_element ret = {
                  (boost::is_void<rtype>::value ? "void" : type_id<rtype>().name())
                , 0 // XXX & result_converter::get_jstype
                , boost::detail::indirect_traits::is_reference_to_non_const<rtype>::value
            };
            js_function_signature_info res = {sig, &ret};
            return res;
        }

    private:
        boost::compressed_pair<F,Policies> data_;
    };

};


#endif // !defined(BOOST_PP_IS_ITERATING)
