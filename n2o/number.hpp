//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_NUMBER_INCLUDED
# define N2O_NUMBER_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/value.hpp>

namespace n2o {

namespace detail {

struct number_base : value {
protected:
    number_base();
    explicit number_base(value_cref rhs);
    explicit number_base(value_cref rhs, value_cref base);

private:
    static v8::Handle<v8::Value> call(value const&);
};

} // end of namespace detail

class number : public detail::number_base {
};

} // end of namespace n2o

#endif // N2O_NUMBER_INCLUDED
