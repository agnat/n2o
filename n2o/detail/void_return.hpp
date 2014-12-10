//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_VOID_RETURN_INCLUDED
# define N2O_DETAIL_VOID_RETURN_INCLUDED

# include <n2o/settings.hpp>

namespace n2o { namespace detail {

struct void_return {
    void_return() {}
private:
    void operator=(void_return const&);
};

template <typename T>
struct returnable {
    typedef T type;
};

template <>
struct returnable<void> {
    typedef void_return type;
};

template <> struct returnable<const void>          : returnable<void> {};
template <> struct returnable<volatile void>       : returnable<void> {};
template <> struct returnable<const volatile void> : returnable<void> {};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_VOID_RETURN_INCLUDED
