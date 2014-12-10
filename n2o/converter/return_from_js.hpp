//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_RETURN_FROM_JS_INCLUDED
# define N2O_CONVERTER_RETURN_FROM_JS_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/errors.hpp>
# include <n2o/converter/from_js.hpp>
# include <n2o/detail/void_return.hpp>
# include <n2o/detail/void_ptr.hpp>
# include <n2o/converter/registered_pointee.hpp>
# include <n2o/converter/object_manager.hpp>

namespace n2o { namespace converter {

template <typename T> struct is_object_manager;

namespace detail {

template <typename T>
struct return_pointer_from_js {
    typedef T result_type;
    result_type operator()(v8::Handle<v8::Value>) const;
};

template <typename T>
struct return_reference_from_js {
    typedef T result_type;
    result_type operator()(v8::Handle<v8::Value>) const;
};

template <typename T>
struct return_rvalue_from_js {
    typedef T result_type;

    return_rvalue_from_js();
    result_type operator()(v8::Handle<v8::Value>);
private:
    rvalue_from_js_data<T> data_;
};

template <typename T>
struct return_object_manager_from_js {
    typedef T result_type;
    result_type operator()(v8::Handle<v8::Value>) const;
};

template <typename T>
struct select_return_from_js {
    static const bool obj_mgr = is_object_manager<T>::value;
    static const bool ptr     = boost::is_pointer<T>::value;
    static const bool ref     = boost::is_reference<T>::value;

    typedef typename boost::mpl::if_c<
          obj_mgr
        , return_object_manager_from_js<T>
        , typename boost::mpl::if_c<
              ptr
            , return_pointer_from_js<T>
            , typename boost::mpl::if_c<
                  ref
                , return_reference_from_js<T>
                , return_rvalue_from_js<T>
            >::type
        >::type
    >::type type;
};

} // end of namespace detail

template <typename T>
struct return_from_js : detail::select_return_from_js<T>::type {};

template <>
struct return_from_js<void> {
    typedef n2o::detail::returnable<void>::type result_type;

    result_type operator()(v8::Handle<v8::Value> x) const {
        (void_result_from_js)(x);
        return result_type();
    }
};


//=== Implementation ===========================================================

namespace detail {

template <typename T>
inline
return_rvalue_from_js<T>::return_rvalue_from_js()
    : data_(const_cast<registration*>(&registered<T>::converters))
{}

template <typename T>
inline
typename return_rvalue_from_js<T>::result_type
return_rvalue_from_js<T>::operator()(v8::Handle<v8::Value> x) {
    return *(T*)(rvalue_result_from_js)(x, data_.stage1);
}

template <typename T>
inline
T
return_reference_from_js<T>::operator()(v8::Handle<v8::Value> v) const {
    return n2o::detail::void_ptr_to_reference(
          (reference_result_from_js)(v, registered<T>::converters)
        , (T(*)())0);
}

template <typename T>
inline
T
return_pointer_from_js<T>::operator()(v8::Handle<v8::Value> v) const {
    return T((pointer_result_from_js)(v, registered_pointee<T>::converters));
}

template <typename T>
inline
T
return_object_manager_from_js<T>::operator()(v8::Handle<v8::Value> v) const {
    return T(object_manager_traits<T>::adopt(expect_non_null(v)));
}

} // end of namespace detail

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_RETURN_FROM_JS_INCLUDED
