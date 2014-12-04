//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_RVALUE_FROM_JS_DATA_INCLUDED
# define N2O_RVALUE_FROM_JS_DATA_INCLUDED

# include <stddef.h>

# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/add_cv.hpp>

# include <boost/static_assert.hpp>

# include <n2o/converter/constructor_function.hpp>
# include <n2o/detail/referent_storage.hpp>
# include <n2o/detail/destroy.hpp>

namespace n2o { namespace converter {

struct rvalue_from_js_stage1_data {
    void * convertible;
    constructor_function construct;
};

template <typename T>
struct rvalue_from_js_storage {
    rvalue_from_js_stage1_data stage1;

    typename n2o::detail::referent_storage<
        typename boost::add_reference<T>::type
    >::type storage;
};


template <typename T>
struct rvalue_from_js_data : rvalue_from_js_storage<T> {
    BOOST_STATIC_ASSERT(offsetof(rvalue_from_js_storage<T>, stage1) == 0);

    rvalue_from_js_data(rvalue_from_js_stage1_data const&);

    rvalue_from_js_data(void* convertible);
    ~rvalue_from_js_data();
  private:
    typedef typename boost::add_reference<
        typename boost::add_cv<T>::type
    >::type ref_type;
};

template <typename T>
inline
rvalue_from_js_data<T>::rvalue_from_js_data(rvalue_from_js_stage1_data const& s1) {
    this->stage1 = s1;
}

template <typename T>
inline
rvalue_from_js_data<T>::rvalue_from_js_data(void * convertible) {
    this->stage1.convertible = convertible;
}

template <typename T>
inline
rvalue_from_js_data<T>::~rvalue_from_js_data() {
    if (this->stage1.convertible == this->storage.bytes) {
        n2o::detail::destroy_referent<ref_type>(this->storage.bytes);
    }
}

}} // end of namespace n2o::converter

#endif // N2O_RVALUE_FROM_JS_DATA_INCLUDED
