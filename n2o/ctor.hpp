#ifndef N2O_CTOR_INCLUDED
#define N2O_CTOR_INCLUDED

#include "config.h"

#include <iostream>

#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <boost/preprocessor/enum_params.hpp>

#include <boost/mpl/void.hpp>


#define N2O_OVERLOAD_TYPES_WITH_DEFAULT \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
        N2O_MAX_ARITY, \
        class T, \
        boost::mpl::void_)

#define N2O_OVERLOAD_TYPES \
    BOOST_PP_ENUM_PARAMS_Z(1, \
        N2O_MAX_ARITY, \
        class T)


namespace n2o {

template <N2O_OVERLOAD_TYPES_WITH_DEFAULT>
class ctor;

template <N2O_OVERLOAD_TYPES>
class ctor {
    public:
        static
        void
        call(v8::FunctionCallbackInfo<v8::Value> const& args) {
            std::cout << "ctor called" << std::endl;
            //return v8::Undefined(v9::Isolate::GetCurrent());
        }
};

} // end of namespace n2o

#endif // N2O_CTOR_INCLUDED
