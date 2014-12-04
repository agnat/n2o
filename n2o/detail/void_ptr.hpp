//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_VOID_PTR_INCLUDED
#define N2O_DETAIL_VOID_PTR_INCLUDED

namespace n2o { namespace detail {

template <typename U>
inline
U& void_ptr_to_reference(void const volatile* p, U&(*)()) {
    return *(U*)(p);
}

template <typename T>
inline
void
write_void_ptr(void const volatile* storage, void* ptr, T*) {
    *(T**)storage = (T*)ptr;
}

template <typename U>
inline
void
write_void_ptr_reference(void const volatile* storage, void* ptr, U&(*)()) {
    typedef typename boost::remove_cv<U>::type u_stripped;
    write_void_ptr(storage, ptr, u_stripped(0));
}

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_VOID_PTR_INCLUDED
