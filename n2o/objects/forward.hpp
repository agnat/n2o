//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_OBJECTS_FORWARD_INCLUDED
# define N2O_OBJECTS_FORWARD_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/if.hpp>
# include <boost/mpl/or.hpp>
# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/add_const.hpp>
# include <boost/type_traits/is_scalar.hpp>
# include <boost/ref.hpp>

# include <n2o/detail/copy_ctor_mutates_rhs.hpp>
# include <n2o/detail/value_arg.hpp>

namespace n2o { namespace objects {

template <typename T>
struct reference_to_value {
    typedef typename boost::add_reference<typename boost::add_const<T>::type> reference;

    reference_to_value(reference x) : value_(x) {}
    reference get() const { return value_; }
private:
    reference value_;
};

template <typename T>
struct forward
    : boost::mpl::if_<
          boost::mpl::or_<n2o::detail::copy_ctor_mutates_rhs<T>, boost::is_scalar<T> >
        , T
        , reference_to_value<T>
    >
{};

template <typename T>
struct unforward {
    typedef typename boost::unwrap_reference<T>::type & type;
};

template <typename T>
struct unforward<reference_to_value<T> > {
    typedef T type;
};

template <typename T>
struct unforward_cref 
    : n2o::detail::value_arg<typename boost::unwrap_reference<T>::type>
{};

template <typename T>
struct unforward_cref<reference_to_value<T> >
    : boost::add_reference<typename boost::add_const<T>::type>
{};
    
}} // end of namespace n2o::objects

#endif // N2O_OBJECTS_FORWARD_INCLUDED
