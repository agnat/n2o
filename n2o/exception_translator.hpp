//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_EXCEPTION_TRANSLATOR_INCLUDED
#define N2O_EXCEPTION_TRANSLATOR_INCLUDED

#include <boost/bind.hpp>
#include <boost/type.hpp>

#include <n2o/detail/translate_exception.hpp>
#include <n2o/detail/exception_handler.hpp>

namespace n2o {

template <class ExceptionType, class Translate>
void
register_exception_translator(Translate translate, boost::type<ExceptionType>* = 0) {
    detail::register_exception_handler(
        boost::bind<bool>(detail::translate_exception<ExceptionType, Translate>(), _1, _2, translate));
}

} // end of namespace n2o
#endif // N2O_EXCEPTION_TRANSLATOR_INCLUDED
