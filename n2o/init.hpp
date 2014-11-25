#ifndef N2O_INIT_INCLUDED
#define N2O_INIT_INCLUDED

#include "config.h"

#include <iostream>

#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <boost/preprocessor/enum_params.hpp>

#include <boost/mpl/void.hpp>


#define N2O_OVERLOAD_TYPES_WITH_DEFAULT  \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
        N2O_MAX_ARITY,                   \
        typename T,                      \
        boost::mpl::void_)

#define N2O_OVERLOAD_TYPES    \
    BOOST_PP_ENUM_PARAMS_Z(1, \
        N2O_MAX_ARITY, \
        typename T)

#define N2O_OVERLOAD_ARGS     \
    BOOST_PP_ENUM_PARAMS_Z(1, \
        N2O_MAX_ARITY,        \
        T)

namespace n2o {

template <N2O_OVERLOAD_TYPES_WITH_DEFAULT>
class init;

template <N2O_OVERLOAD_TYPES_WITH_DEFAULT>
class optional;


namespace detail {

template <typename T>
struct is_optional : boost::mpl::false_ {};

template <N2O_OVERLOAD_TYPES>
struct is_optional<optional<N2O_OVERLOAD_ARGS> > : boost::mpl::true_ {};

template <int NDefaults>
struct define_class_init_helper;

} // end of namespace detail

template <typename DerivedT>
struct init_base {
    DerivedT const& derived() const {
        return *static_cast<DerivedT const*>(this);
    }

    static
    default_call_policies call_policies() {
        return default_call_policies();
    }
};

template <typename CallPoliciesT, typename InitT>
class init_with_call_policies : public init_base<init_with_call_policies<CallPoliciesT, InitT> >
{
    typedef init_base<init_with_call_policies<CallPoliciesT, InitT> > base;
public:
    typedef typename InitT::n_arguments n_arguments;
    typedef typename InitT::n_defaults  n_defaults;
    typedef typename InitT::signature signature;

    init_with_call_policies(CallPoliciesT const& policies) : 
        base(), policies_(policies) 
    {}

    CallPoliciesT const& call_policies() const {
        return this->policies_;
    }
private:
    CallPoliciesT policies_;
};

template <N2O_OVERLOAD_TYPES>
class init : public init_base<init<N2O_OVERLOAD_ARGS> > {
    typedef init_base<init<N2O_OVERLOAD_ARGS> > base;
public:
    static
    void
    call(v8::FunctionCallbackInfo<v8::Value> const& args) {
        std::cout << "init called" << std::endl;
        if ( ! args.IsConstructCall()) {
            js_error("constructor called without 'new'");
            //throw_error_already_set();
            return; // XXX better throw...
        }
    }
};

} // end of namespace n2o

#undef N2O_OVERLOAD_TYPES_WITH_DEFAULT
#undef N2O_OVERLOAD_TYPES
#undef N2O_OVERLOAD_ARGS

#endif // N2O_INIT_INCLUDED
