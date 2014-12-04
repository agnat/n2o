//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_DESTROY_INCLUDED
#define N2O_DETAIL_DESTROY_INCLUDED

#include <boost/type_traits/is_array.hpp>

namespace n2o { namespace detail {

template <bool array> struct value_destroyer;

template <>
struct value_destroyer<false> {
    template <typename T>
    static
    void
    execute(T const volatile * p) {
        p->~T();
    }
};

template <>
struct value_destroyer<true> {
    template <typename A, typename T>
    static
    void
    execute(A*, T const volatile * const first) {
        for (T const volatile * p = first; p != first + sizeof(A)/sizeof(T); ++p) {
            value_destroyer<boost::is_array<T>::value>::execute(p);
        }
    }

    template <typename T>
    static
    void
    execute(T const volatile * p) {
        execute(p, *p);
    }
};

template <typename T>
inline
void
destroy_referent_impl(void* p, T&(*)()) {
    value_destroyer<boost::is_array<T>::value>::execute((const volatile T*)p);
}

template <typename T>
inline
void
destroy_referent(void* p, T(*)() = 0) {
    destroy_referent_impl(p, (T(*)())0);
}

}} // end of namespace detail, n2o

#endif // N2O_DETAIL_DESTROY_INCLUDED
