#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
# ifndef N2O_DETAIL_SIGNATURE_INCLUDED
#  define N2O_DETAIL_SIGNATURE_INCLUDED

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/iteration/local.hpp>
#  include <boost/mpl/at.hpp>
#  include <boost/mpl/size.hpp>

#  include <n2o/type_id.hpp>
#  include <n2o/detail/indirect_traits.hpp>
#  include <n2o/converter/jstype_function.hpp>

namespace n2o { namespace detail {

struct signature_element {
    char const* basename;
    converter::jstype_function jstype_f;
    bool lvalue;
};

struct js_function_signature_info {
    signature_element const* signature;
    signature_element const* ret;
};

template <unsigned> struct signature_arity;

#  define BOOST_PP_ITERATION_PARAMS_1 \
        (3, (0, N2O_MAX_ARITY + 1, <n2o/detail/signature.hpp>))
#  include BOOST_PP_ITERATE()

template <typename Sig>
struct signature_base_select {
    enum { arity = boost::mpl::size<Sig>::value - 1 };
    typedef typename signature_arity<arity>::template impl<Sig> type;
};

template <typename Sig>
struct signature : signature_base_select<Sig>::type {};

}} // end of namespace n2o::detail

# endif // N2O_DETAIL_SIGNATURE_INCLUDED

#else

# define N BOOST_PP_ITERATION()

template <>
struct signature_arity<N> {
    template <typename Sig>
    struct impl {
        static signature_element const* elements() {
            using indirect_traits::is_reference_to_non_const;
            using boost::mpl::at_c;
            using converter::expected_jstype_for_arg;
            static signature_element const result[N+2] = {
# define BOOST_PP_LOCAL_MACRO(i)                                                   \
                {                                                                  \
                  type_id<typename at_c<Sig,i>::type>().name()                     \
                , &expected_jstype_for_arg<typename at_c<Sig,i>::type>::get_jstype \
                , is_reference_to_non_const<typename at_c<Sig,i>::type>::value     \
                },

# define BOOST_PP_LOCAL_LIMITS (0, N)
# include BOOST_PP_LOCAL_ITERATE()
                {0, 0, 0}
            };
            return result;
        }
    };
};

#endif // BOOST_PP_IS_ITERATING
