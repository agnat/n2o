//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_TYPE_LIST_INCLUDED
# define N2O_TYPE_LIST_INCLUDED

# include <n2o/settings.hpp>

# include <boost/preprocessor/arithmetic/inc.hpp>

# include <n2o/detail/preprocessor.hpp>

# define N2O_LIST_SIZE BOOST_PP_INC(BOOST_PP_INC(N2O_MAX_ARITY))

# if N2O_LIST_SIZE > 48
#  error Arities above 48 not supported by n2o due to boost::mpl internal limit
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

# include <n2o/detail/type_list_impl.hpp>

#endif // N2O_TYPE_LIST_INCLUDED
