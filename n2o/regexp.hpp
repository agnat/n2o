//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_REGEXP_INCLUDED
# define N2O_REGEXP_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/value.hpp>

namespace n2o {

namespace detail {

struct regexp_base : value {
};

} // end of namespace detail

class regexp : public detail::regexp_base {
};

} // end of namespace n2o

#endif // N2O_REGEXP_INCLUDED
