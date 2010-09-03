#ifndef N2O_FUNCTION_WRAPPER
#define N2O_FUNCTION_WRAPPER

#include <v8.h>

namespace n2o { namespace detail {

v8::Local<v8::Object>
get_function_wrapper(void * native_function);

}};
#endif // N2O_FUNCTION_WRAPPER
