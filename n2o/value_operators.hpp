//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_VALUE_OPERATORS_INCLUDED
# define N2O_VALUE_OPERATORS_INCLUDED

# include <n2o/settings.hpp>

# include <boost/iterator/detail/enable_if.hpp>
# include <boost/mpl/bool.hpp>

# include <n2o/value_core.hpp>
# include <n2o/call.hpp>

# include <boost/iterator/detail/config_def.hpp>

namespace n2o { namespace api {

template <typename X>
char
is_value_operators_helper(value_operators<X> const*);

typedef char (&no_type)[2];
no_type is_value_operators_helper(...);

template <typename X>
X*
make_ptr();

template <typename L, typename R = L>
struct is_value_operators {
    enum {
        value
        = (sizeof(api::is_value_operators_helper(api::make_ptr<L>()))
           + sizeof(api::is_value_operators_helper(api::make_ptr<R>()))
           < 4)
    };
    typedef boost::mpl::bool_<value> type;
};

template <typename L, typename R, typename T>
struct enable_binary
    : boost::iterators::enable_if<is_value_operators<L,R>, T>
{};

template <typename U>
value
value_operators<U>::operator()() const {
    value const& f = *static_cast<U const*>(this);
    return call<value>(f.handle(), v8::Undefined(v8::Isolate::GetCurrent()));
}

template <typename U>
inline
value_operators<U>::operator bool_type() const {
    // value const& x = *static_cast<U const*>(this);
    // TODO: truth testing
    return 0;
}

# define N2O_BINARY_RETURN(T) typename enable_binary<L,R,T>::type

# define N2O_BINARY_OPERATOR(op)                    \
value                                               \
operator op(value const& lhs, value const& rhs);    \
template <typename L, typename R>                   \
N2O_BINARY_RETURN(value)                            \
operator op(L const& lhs, R const& rhs) {           \
    return value(lhs) op value(rhs);                \
}

N2O_BINARY_OPERATOR(>)
N2O_BINARY_OPERATOR(>=)
N2O_BINARY_OPERATOR(<)
N2O_BINARY_OPERATOR(<=)
N2O_BINARY_OPERATOR(==)
N2O_BINARY_OPERATOR(!=)
N2O_BINARY_OPERATOR(+)
N2O_BINARY_OPERATOR(-)
N2O_BINARY_OPERATOR(*)
N2O_BINARY_OPERATOR(/)
N2O_BINARY_OPERATOR(%)
N2O_BINARY_OPERATOR(<<)
N2O_BINARY_OPERATOR(>>)
N2O_BINARY_OPERATOR(&)
N2O_BINARY_OPERATOR(^)
N2O_BINARY_OPERATOR(|)

# undef N2O_BINARY_OPERATOR


# define N2O_INPLACE_OPERATOR(op)           \
template <typename R>                       \
value &                                     \
operator op(value & lhs, R const& rhs) {    \
    return lhs op value(rhs);               \
}

N2O_INPLACE_OPERATOR(+=)
N2O_INPLACE_OPERATOR(-=)
N2O_INPLACE_OPERATOR(*=)
N2O_INPLACE_OPERATOR(/=)
N2O_INPLACE_OPERATOR(%=)
N2O_INPLACE_OPERATOR(<<=)
N2O_INPLACE_OPERATOR(>>=)
N2O_INPLACE_OPERATOR(&=)
N2O_INPLACE_OPERATOR(^=)
N2O_INPLACE_OPERATOR(|=)

# undef N2O_INPLACE_OPERATOR

}} // end of namespace n2o::api

# include <boost/iterator/detail/config_undef.hpp>

#endif // N2O_VALUE_OPERATORS_INCLUDED
