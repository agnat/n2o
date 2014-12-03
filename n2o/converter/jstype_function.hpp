#ifndef N2O_CONVERTER_JSTYPE_FUNCTION_INCLUDED
# define N2O_CONVERTER_JSTYPE_FUNCTION_INCLUDED

# include <n2o/js_type_info.hpp>
# include <n2o/detail/unwind_type.hpp>

namespace n2o { namespace converter {

typedef js_type_info const* (*jstype_function)();

namespace detail {

struct unwind_type_id_helper {
    typedef n2o::type_info result_type;

    template <class U>
    static
    result_type
    execute(U*) {
        return n2o::type_id<U>();
    }
};

template <typename T>
inline
n2o::type_info
unwind_type_id_(boost::type<T>* = 0, boost::mpl::false_ * = 0) {
    return n2o::detail::unwind_type<unwind_type_id_helper, T>();
}

inline
n2o::type_info
unwind_type_id_(boost::type<void>* = 0, boost::mpl::true_* = 0) {
    return type_id<void>();
}

template <typename T>
inline
n2o::type_info
unwind_type_id(boost::type<T> * p = 0) {
    return unwind_type_id_(p, (boost::mpl::bool_<boost::is_void<T>::value >*)0);
}

} // end of namespace detail

template <typename T>
struct expected_jstype_for_arg {
    static js_type_info const* get_jstype() {
        const converter::registration * r = registry::query(
            detail::unwind_type_id((boost::type<T>*)0, (boost::mpl::bool_<boost::is_void<T>::value>*)0)
            );
        return r ? r->expected_from_js_type() : 0;
    }
};

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_JSTYPE_FUNCTION_INCLUDED
