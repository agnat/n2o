//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_REGISTERED_INCLUDED
# define N2O_CONVERTER_REGISTERED_INCLUDED

# include <boost/shared_ptr.hpp>
# include <boost/type.hpp>

# include <n2o/converter/registry.hpp>


namespace n2o { namespace converter {

struct registration;

namespace detail {
    template <typename T>
    struct registered_base {
        static registration const& converters;
    };
}

template <typename T>
struct registered :
    detail::registered_base<
        typename boost::add_reference<
            typename boost::add_cv<T>::type
        >::type
    >
{};

template <typename T> struct registered<T&> : registered<T> {};

namespace detail {

inline
void
register_shared_ptr0(...) {}

template <typename T>
void
register_shared_ptr0(boost::shared_ptr<T>*) {
    registry::lookup_shared_ptr(type_id<boost::shared_ptr<T> >());
}

template <typename T> inline
void
register_shared_ptr1(T const volatile*) {
    detail::register_shared_ptr0((T*)0);
}

template <typename T> inline
registration const&
registry_lookup2(T&(*)()) {
    detail::register_shared_ptr1((T*)0);
    return registry::lookup(type_id<T&>());
}

template <typename T> inline
registration const&
registry_lookup1(boost::type<T>) {
    return registry_lookup2((T(*)())0);
}

inline
registration const&
registry_lookup1(boost::type<const volatile void>) {
    detail::register_shared_ptr1((void*)0);
    return registry::lookup(type_id<void>());
}

template <typename T>
registration const&
registered_base<T>::converters = detail::registry_lookup1(boost::type<T>());
} // end of namespace detail


}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_REGISTERED_INCLUDED
