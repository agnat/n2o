//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_STRING_LITERAL_INCLUDED
# define N2O_DETAIL_STRING_LITERAL_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/bool.hpp>

namespace n2o { namespace detail {

template <typename T>
struct is_string_literal : boost::mpl::false_ {};

template <std::size_t n>
struct is_string_literal<char const[n]> : boost::mpl::true_ {};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_STRING_LITERAL_INCLUDED
