#ifndef N2O_DETAIL_TRANSLATE_EXCEPTION_INCLUDED
#define N2O_DETAIL_TRANSLATE_EXCEPTION_INCLUDED

#include <boost/call_traits.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/function/function0.hpp>

#include <n2o/detail/exception_handler.hpp>

namespace n2o { namespace detail {

template <typename ExceptionType, typename Translate>
struct translate_exception {
    typedef typename boost::add_reference<
        typename boost::add_const<ExceptionType>::type
    >::type exception_cref;

    inline
    bool
    operator()(
          exception_handler const& handler
        , boost::function0<void> const& f
        , typename boost::call_traits<Translate>::param_type translate) const
    {
        try {
            return handler(f);
        } catch (exception_cref ex) {
            translate(ex);
            return true;
        }
    }
};

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_TRANSLATE_EXCEPTION_INCLUDED
