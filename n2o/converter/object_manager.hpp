//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_OBJECT_MANAGER_INCLUDED
# define N2O_CONVERTER_OBJECT_MANAGER_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/bool.hpp>

namespace n2o {

namespace api { class value; }

namespace converter {

template <typename T>
struct default_object_manager_traits {
    static const bool is_specialized = false; // XXX n2o::detail::is_borrowed_ptr<T>::value;
};

template <typename T>
struct object_manager_traits : default_object_manager_traits<T> {};

template <typename T>
struct is_object_manager
    : boost::mpl::bool_<object_manager_traits<T>::is_specialized>
{};

template <typename T>
struct is_reference_to_object_manager : boost::mpl::false_ {};

template <typename T>
struct is_reference_to_object_manager<T&> : is_object_manager<T> {};

template <typename T>
struct is_reference_to_object_manager<T const&> : is_object_manager<T> {};

template <typename T>
struct is_reference_to_object_manager<T volatile&> : is_object_manager<T> {};

template <typename T>
struct is_reference_to_object_manager<T const volatile&> : is_object_manager<T> {};

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_OBJECT_MANAGER_INCLUDED
