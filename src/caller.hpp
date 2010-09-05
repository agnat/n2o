#ifndef N2O_CALLER_INCLUDED
#define N2O_CALLER_INCLUDED

#include "config.h"

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/at.hpp>

#include <iostream>


#include "function_wrapper.hpp"

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

template <typename F, typename CallPolicies, typename Sig>
class caller {
    public:
        static
        v8::Handle<v8::Value>
        create(F f) {
            return v8::External::Wrap(new caller(f)); // XXX never deleted
        }


        static
        v8::Handle<v8::Value>
        call(v8::Arguments const& args) {
            caller * f = reinterpret_cast<caller*>(v8::External::Unwrap(args.Data()));
            return (*f)(args);
        }

        v8::Handle<v8::Value>
        operator()(v8::Arguments const& args) {
            typedef typename boost::mpl::begin<Sig>::type first;
            typedef typename first::type result_t;
            typedef typename select_result_converter<CallPolicies, result_t>::type result_converter;
            return detail::invoke(
                    detail::invoke_tag<result_t, F>(),
                    result_converter(),
                    native_func_);
        }
    private:
        caller();
        caller(F f) : native_func_(f) {}

        F native_func_;
};

}} // end of namespace detail, n2o

#endif // N2O_CALLER_INCLUDED
