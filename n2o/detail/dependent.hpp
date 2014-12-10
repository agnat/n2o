//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_DEPENDENT_INCLUDED
# define N2O_DETAIL_DEPENDENT_INCLUDED

# include <n2o/settings.hpp>

namespace n2o { namespace detail {

// From boost::python
// A way to turn a concrete type T into a type dependent on U. This
// keeps conforming compilers (those implementing proper 2-phase
// name lookup for templates) from complaining about incomplete
// types in situations where it would otherwise be inconvenient or
// impossible to re-order code so that all types are defined in time.

// One such use is when we must return an incomplete T from a member
// function template (which must be defined in the class body to
// keep MSVC happy).

template <typename T, typename U>
struct dependent {
    typedef T type;
};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_DEPENDENT_INCLUDED
