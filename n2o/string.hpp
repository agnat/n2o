//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_STRING_INCLUDED
# define N2O_STRING_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/value.hpp>

namespace n2o {

namespace detail {

struct string_base : value {
};

} // end of namespace detail


class string : public detail::string_base {
};

} // end of namespace n2o

#endif // N2O_STRING_INCLUDED
