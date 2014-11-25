#ifndef N2O_PREPROCESSOR_INCLUDED
# define N2O_PREPROCESSOR_INCLUDED

# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>

# define N2O_APPLY(x) BOOST_PP_CAT(N2O_APPLY_, x)

# define N2O_APPLY_N2O_ITEM(v) v
# define N2O_APPLY_N2O_NIL


#  define N2O_CV_COUNT 4

# define N2O_CV_QUALIFIER(i)                          \
    N2O_APPLY(                                        \
        BOOST_PP_TUPLE_ELEM(4, i, N2O_CV_QUALIFIER_I) \
    )

# define N2O_CV_QUALIFIER_I      \
    (                            \
        N2O_NIL,                 \
        N2O_ITEM(const),         \
        N2O_ITEM(volatile),      \
        N2O_ITEM(const volatile) \
    )

# define N2O_FIXED(z, n, text) text

#endif //  N2O_PREPROCESSOR_INCLUDED
