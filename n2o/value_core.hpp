//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_OBJECT_OBJECT_BASE_INCLUDED
# define N2O_OBJECT_OBJECT_BASE_INCLUDED

# include <n2o/settings.hpp>

# include <boost/preprocessor/iterate.hpp>
# include <boost/type_traits/is_convertible.hpp>

# include <n2o/detail/is_xxx.hpp>
# include <n2o/detail/dependent.hpp>
# include <n2o/errors.hpp>
# include <n2o/call.hpp>
# include <n2o/tag.hpp>
# include <n2o/objects/forward.hpp>

namespace n2o {

namespace detail {
    class args_proxy;
}

namespace converter {
    template <typename T> struct arg_to_js;
}

namespace api {

template <typename Policies> class proxy;

struct const_property_policies;
struct property_policies;

typedef proxy<const_property_policies> const_object_property;
typedef proxy<property_policies> object_property;

N2O_IS_XXX_DEF(proxy, n2o::api::proxy, 1)

template <typename T> struct value_initializer;

class value;
typedef v8::Handle<v8::Value> (value::*bool_type)() const;

template <typename U>
class value_operators {
protected:
    typedef value const& value_cref;
public:
    value operator()() const;

# define BOOST_PP_ITERATION_PARAMS_1 (3, (1, N2O_MAX_ARITY, <n2o/value_call.hpp>))
# include BOOST_PP_ITERATE()

    detail::args_proxy operator* () const;
    value operator()(detail::args_proxy const& args) const;

    operator bool_type() const;

    const_object_property operator[](value_cref) const;
    object_property operator[](value_cref);

    template <typename T>
    const_object_property
    operator[](T const& key) const;

    template <typename T>
    object_property
    operator[](T const& key);
};

struct value_base : value_operators<value> {
    inline value_base(value_base const&);
    inline value_base(v8::Handle<v8::Value> v);

    inline value_base& operator=(value_base const& rhs);

    inline v8::Handle<v8::Value> handle() const;

    inline bool is_undefined() const;
private:
    v8::Handle<v8::Value> value_;
};

template <typename T, typename U>
struct is_derived : 
    boost::is_convertible<
          typename boost::remove_reference<T>::type*
        , U const*
    >
{};

template <typename T>
typename objects::unforward_cref<T>::type
do_unforward_cref(T const& x) {
    return x;
}

template <typename T>
v8::Handle<v8::Value>
value_base_initializer(T const& x) {
    typedef typename is_derived<
          typename objects::unforward_cref<T>::type
        , value
    >::type is_value;

    return value_initializer<typename boost::unwrap_reference<T>::type>::get(x, is_value());
}

class value : public value_base {
public:
    value();

    template <typename T>
    explicit value(T const& x) : value_base(value_base_initializer(x))
    {}
};

} // end of namespace api

} // end of namespace n2o

#endif // N2O_OBJECT_OBJECT_BASE_INCLUDED
