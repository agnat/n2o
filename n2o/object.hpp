//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_OBJECT_INCLUDED
# define N2O_OBJECT_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/value.hpp>

namespace n2o {

namespace detail {

struct object_base : value {

protected:
    explicit object_base(value_cref other);
};

} // end of namespace detail

class object : public detail::object_base {
    typedef detail::object_base base;
  public:

    template <typename T>
    explicit object(T const& other) : base(value(other)) {}
};

}

#endif // N2O_OBJECT_INCLUDED
