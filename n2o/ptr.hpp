//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_PTR_INCLUDED
# define N2O_PTR_INCLUDED

# include <n2o/settings.hpp>

# include <boost/mpl/bool.hpp>

namespace n2o {

template <typename Ptr> class pointer_wrapper {
public:
    typedef Ptr type;

    explicit pointer_wrapper(Ptr x) : p_(x) {}
    operator Ptr() const { return p_; }
    Ptr get() const { return p_; }
private:
    Ptr p_;
};

template <typename T>
inline
pointer_wrapper<T>
ptr(T t) {
    return pointer_wrapper<T>(t);
}

template <typename T>
struct is_pointer_wrapper : boost::mpl::false_ {};

template <typename T>
struct is_pointer_wrapper<pointer_wrapper<T> > : boost::mpl::true_ {};

template <typename T>
struct unwrap_pointer {
    typedef T type;
};

template <typename T>
struct unwrap_pointer<pointer_wrapper<T> > {
    typedef T type;
};

} // end of namespace n2o
#endif // N2O_PTR_INCLUDED
