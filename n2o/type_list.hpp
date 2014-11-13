#ifndef N2O_TYPE_LIST_INCLUDED
# define N2O_TYPE_LIST_INCLUDED

#include "config.h"

# include <boost/preprocessor/arithmetic/inc.hpp>

# define N2O_LIST_SIZE BOOST_PP_INC(BOOST_PP_INC(N2O_MAX_ARITY))

# if N2O_LIST_SIZE > 48
#  error Arities above 48 not supported by n2o due to MPL internal limit
# elif N2O_LIST_SIZE > 38
#  include <boost/mpl/vector/vector50.hpp>
# elif N2O_LIST_SIZE > 28
#  include <boost/mpl/vector/vector40.hpp>
# elif N2O_LIST_SIZE > 18
#  include <boost/mpl/vector/vector30.hpp>
# elif N2O_LIST_SIZE > 8
#  include <boost/mpl/vector/vector20.hpp>
# else
#  include <boost/mpl/vector/vector10.hpp>
# endif

#endif // N2O_TYPE_LIST_INCLUDED
