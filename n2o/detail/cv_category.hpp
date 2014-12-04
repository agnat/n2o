//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_DETAIL_CV_CATEGORY_INCLUDED
# define N2O_DETAIL_CV_CATEGORY_INCLUDED

namespace n2o { namespace detail {

template <bool is_const_, bool is_volatile_>
struct cv_tag {
    static const bool is_const = is_const_;
    static const bool is_volatile = is_volatile_;
};

typedef cv_tag<false,false> cv_unqualified;
typedef cv_tag<true,false> const_;
typedef cv_tag<false,true> volatile_;
typedef cv_tag<true,true> const_volatile_;

template <typename T>
struct cv_category {
    typedef cv_tag<
          boost::is_const<T>::value
        , boost::is_volatile<T>::value
    > type;
};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_CV_CATEGORY_INCLUDED
