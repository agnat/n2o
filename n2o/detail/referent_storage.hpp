//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_REFERENT_STORAGE_INCLUDED
# define N2O_DETAIL_REFERENT_STORAGE_INCLUDED

# include <boost/mpl/if.hpp>

namespace n2o { namespace detail {

struct alignment_dummy;
typedef void (*function_ptr)();
typedef int (alignment_dummy::*member_ptr);
typedef int (alignment_dummy::*member_function_ptr)();

# define N2O_ALIGNER(T, n)                      \
    typename boost::mpl::if_c<                  \
        sizeof(T) <= size, T, char>::type t##n

template <size_t size>
union aligned_storage {
    N2O_ALIGNER(char,                 0);
    N2O_ALIGNER(short,                1);
    N2O_ALIGNER(int,                  2);
    N2O_ALIGNER(long,                 3);
    N2O_ALIGNER(float,                4);
    N2O_ALIGNER(double,               5);
    N2O_ALIGNER(long double,          6);
    N2O_ALIGNER(void*,                7);
    N2O_ALIGNER(function_ptr,         8);
    N2O_ALIGNER(member_ptr,           9);
    N2O_ALIGNER(member_function_ptr, 10);
    char bytes[size];
};

# undef N2O_ALIGNER

template <class T> struct referent_size;

template <typename T>
struct referent_size<T&> {
    BOOST_STATIC_CONSTANT(size_t, value = sizeof(T));
};

template <typename T>
struct referent_storage {
    typedef aligned_storage<referent_size<T>::value> type;
};

}} // end of namespace detail, n2o

#endif // N2O_DETAIL_REFERENT_STORAGE_INCLUDED
