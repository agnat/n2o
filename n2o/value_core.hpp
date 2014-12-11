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

typedef proxy<const_property_policies> const_value_property;
typedef proxy<property_policies> value_property;

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

    const_value_property operator[](value_cref) const;
    value_property operator[](value_cref);

    template <typename T>
    const_value_property
    operator[](T const& key) const;

    template <typename T>
    value_property
    operator[](T const& key);
};

struct value_base : value_operators<value> {
    inline value_base(value_base const&);
    inline value_base(v8::Handle<v8::Value> v);
    inline ~value_base();

    inline value_base& operator=(value_base const& rhs);

    inline v8::Handle<v8::Value> handle() const;

    inline bool is_undefined() const;
private:
    v8::Handle<v8::Value> handle_;
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
    explicit value(v8::Handle<T> x) : value_base(x) {}

    template <typename T>
    explicit value(T const& x) : value_base(value_base_initializer(x))
    {}

};

template <bool is_proxy = false, bool is_object_manager = false>
struct value_initializer_impl {
    static
    v8::Handle<v8::Value>
    get(value const& x, boost::mpl::true_) {
        return x.handle();
    }

    template <typename T>
    static
    v8::Handle<v8::Value>
    get(T const& x, boost::mpl::false_) {
        return converter::arg_to_js<T>(x).get();
    }
};

template <>
struct value_initializer_impl<true, false> {
    template <typename Policies>
    static
    v8::Handle<v8::Value>
    get(proxy<Policies> const& x, boost::mpl::false_) {
        return x.operator value().handle();
    }
};

template <>
struct value_initializer_impl<false, true> {
    template <typename T, typename U>
    static
    v8::Handle<v8::Value>
    get(T const& x, U) {
        return get_managed_object(x, n2o::tag);
    }
};

template <>
struct value_initializer_impl<true, true> {};

template <typename T>
struct value_initializer : value_initializer_impl<
      is_proxy<T>::value
    , converter::is_object_manager<T>::value
>
{};

} // end of namespace api

using api::value;

template <typename T> struct extract;


//=== Implementation ===========================================================

namespace detail {

class call_proxy {
public:
    call_proxy(value target) : target_(target) {}
    operator value() const { return target_; }
private:
    value target_;
};

class args_proxy : public call_proxy {
public:
    args_proxy(value v) : call_proxy(v) {}
};

} // end of namespace detail


template <typename U>
value
api::value_operators<U>::operator()(detail::args_proxy const& args) const {
    U const& self = *static_cast<U const*>(this);
    
    // TODO:

    return value();
}

inline
value::value() : value_base(v8::Undefined(v8::Isolate::GetCurrent())) {}

inline
api::value_base::value_base(value_base const& rhs) : handle_(rhs.handle_) {}

inline
api::value_base::value_base(v8::Handle<v8::Value> v) : handle_(v) {}

inline
api::value_base &
api::value_base::operator=(api::value_base const& rhs) {
    this->handle_ = rhs.handle_;
    return *this;
}

inline
api::value_base::~value_base() {}

inline
v8::Handle<v8::Value>
api::value_base::handle() const { return handle_; }

//=== Converter Specializations ================================================

namespace converter {

template <typename T> struct object_manager_traits;

template <>
struct object_manager_traits<value> {
    static const bool is_specialized = true;
    static
    bool
    check(v8::Handle<v8::Value>) { return true; }

    static
    v8::Handle<v8::Value>
    adopt(v8::Handle<v8::Value> x) {
        return x;
    }

    static js_type_info const* get_jstype() { return 0; }
};

} // end of namespace converter

inline
v8::Handle<v8::Value>
get_managed_object(value const& x, tag_t) {
    return x.handle();
}

} // end of namespace n2o

#endif // N2O_OBJECT_OBJECT_BASE_INCLUDED
