//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_UNWIND_TYPE_INCLUDED
# define N2O_DETAIL_UNWIND_TYPE_INCLUDED

# include <boost/type_traits/object_traits.hpp>

# include <n2o/detail/cv_category.hpp>
# include <n2o/detail/indirect_traits.hpp>

namespace n2o { namespace detail {

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_type_cv(U * p, cv_unqualified, Generator* = 0) {
    return Generator::execute(p);
}

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_type_cv(U const* p, const_, Generator* = 0) {
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_type_cv(U volatile* p, volatile_, Generator* = 0) {
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_type_cv(U const volatile* p, const_volatile_, Generator* = 0) {
    return unwind_type(const_cast<U*>(p), (Generator*)0);
}

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_ptr_type(U* p, Generator* = 0) {
    typedef typename cv_category<U>::type tag;
    return unwind_type_cv<Generator>(p, tag());
}

template <bool is_ptr>
struct unwind_helper {
    template <typename Generator, typename U>
    static
    typename Generator::result_type
    execute(U p, Generator* = 0) {
        return unwind_ptr_type(p, (Generator*)0);
    }
};

template <>
struct unwind_helper<false> {
    template <typename Generator, typename U>
    static
    typename Generator::result_type
    execute(U p, Generator* = 0) {
        return unwind_ptr_type(&p, (Generator*)0);
    }
};

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_type(U const& p, Generator*) {
    return unwind_helper<boost::is_pointer<U>::value>::execute(p, (Generator*)0);
}

enum { direct_, pointer_, reference_, reference_to_pointer_ };

template <int indirection> struct unwind_helper2;

template <>
struct unwind_helper2<direct_> {
    template <typename Generator, typename U>
    static
    typename Generator::result_type
    execute(U(*)(), Generator* = 0) {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }
};

template <>
struct unwind_helper2<pointer_> {
    template <typename Generator, typename U>
    static
    typename Generator::result_type
    execute(U*(*)(), Generator* = 0) {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }
};

template <>
struct unwind_helper2<reference_> {
    template <typename Generator, typename U>
    static
    typename Generator::result_type
    execute(U&(*)(), Generator* = 0) {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }
};

template <>
struct unwind_helper2<reference_to_pointer_> {
    template <typename Generator, typename U>
    static
    typename Generator::result_type
    execute(U&(*)(), Generator* = 0) {
        return unwind_ptr_type(U(0), (Generator*)0);
    }
};

template <typename Generator, typename U>
inline
typename Generator::result_type
unwind_type(boost::type<U>*p, Generator*) {
    static const int indirection
        = (boost::is_pointer<U>::value ? pointer_ : 0)
                + (indirect_traits::is_reference_to_pointer<U>::value
                ? reference_to_pointer_
                : boost::is_reference<U>::value
                ? reference_
                : 0);
    return unwind_helper2<indirection>::execute((U(*)())0, (Generator*)0);
}

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_UNWIND_TYPE_INCLUDED
