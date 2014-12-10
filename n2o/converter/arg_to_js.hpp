//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_ARG_TO_JS_INCLUDED
# define N2O_CONVERTER_ARG_TO_JS_INCLUDED

# include <n2o/settings.hpp>

# include <iostream>

# include <boost/ref.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/or.hpp>
# include <boost/type_traits/function_traits.hpp>

# include <n2o/converter/arg_to_js_base.hpp>
# include <n2o/converter/builtin_converters.hpp>
# include <n2o/detail/string_literal.hpp>
# include <n2o/detail/value_is_shared_ptr.hpp>
# include <n2o/detail/indirect_traits.hpp>
# include <n2o/ptr.hpp>

namespace n2o { namespace converter {

template <typename T> struct is_object_manager;

namespace detail {

template <typename T>
struct function_arg_to_js {
    function_arg_to_js(T const& x);
};

template <typename T>
struct reference_arg_to_js {
    reference_arg_to_js(T & x);
private:
    static v8::Handle<v8::Value> get_value(T & x);
};

template <typename T>
struct shared_ptr_arg_to_js {
    shared_ptr_arg_to_js(T const& x);
private:
    static v8::Handle<v8::Value> get_value(T & x);
};

template <typename T>
struct value_arg_to_js : arg_to_js_base {
    value_arg_to_js(T const&);
};

template <typename Ptr>
struct pointer_deep_arg_to_js : arg_to_js_base {
    pointer_deep_arg_to_js(Ptr);
};

template <typename Ptr>
struct pointer_shallow_arg_to_js {
    pointer_shallow_arg_to_js(Ptr);
private:
    static v8::Handle<v8::Value> get_value(Ptr p);
};

template <typename T>
struct object_manager_arg_to_js {
    object_manager_arg_to_js(T const& x) : src_(x) {}

    v8::Handle<v8::Value>
    get() const {
        std::cerr << "not implemented" << std::endl;
        // return n2o::upcast<v8::Value>(get_managed_object(src_, tag));
        return v8::Undefined(v8::Isolate::GetCurrent());
    }
private:
    T const& src_;
};

template <typename T>
struct select_arg_to_js {
    typedef typename boost::unwrap_reference<T>::type unwrapped_referent;
    typedef typename n2o::unwrap_pointer<T>::type unwrapped_ptr;

    typedef typename boost::mpl::if_<
        // handle char const[N]; and treat them as char const*
          n2o::detail::is_string_literal<T const>
        , arg_to_js<char const*>
        , typename boost::mpl::if_<
              n2o::detail::value_is_shared_ptr<T>
            , shared_ptr_arg_to_js<T>

            , typename boost::mpl::if_<
                boost::mpl::or_<
                      boost::is_function<T>
                    , indirect_traits::is_pointer_to_function<T>
                    , boost::is_member_function_pointer<T>
                >
                , function_arg_to_js<T>

                , typename boost::mpl::if_<
                      is_object_manager<T>
                    , object_manager_arg_to_js<T>

                    , typename boost::mpl::if_<
                          boost::is_pointer<T>
                        , pointer_deep_arg_to_js<T>

                        , typename boost::mpl::if_<
                              is_pointer_wrapper<T>
                            , pointer_shallow_arg_to_js<unwrapped_ptr>

                            , typename boost::mpl::if_<
                                  boost::is_reference_wrapper<T>
                                , reference_arg_to_js<unwrapped_referent>
                                , value_arg_to_js<T>
                            >::type
                        >::type
                    >::type
                >::type
            >::type
        >::type
    >::type

    type;
};

} // end of namespace detail

template <typename T>
struct arg_to_js : detail::select_arg_to_js<T>::type {
    typedef typename detail::select_arg_to_js<T>::type base;

    arg_to_js(T const& x);
};

//=== Implementation ===========================================================

namespace detail {

} // end of namespace detail

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_ARG_TO_JS_INCLUDED
