//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_REGISTERED_POINTEE_INCLUDED
# define N2O_CONVERTER_REGISTERED_POINTEE_INCLUDED

# include <n2o/settings.hpp>

# include <boost/type_traits/remove_pointer.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/remove_reference.hpp>

# include <n2o/converter/registered.hpp>

namespace n2o { namespace converter {

template <typename T>
struct registered_pointee : 
    registered<
        typename boost::remove_pointer<
            typename boost::remove_cv<
                typename boost::remove_reference<T>::type
            >::type
        >::type
    >
{};

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_REGISTERED_POINTEE_INCLUDED
