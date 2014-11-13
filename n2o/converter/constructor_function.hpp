#ifndef N2O_CONVERTER_CONSTRUCTOR_FUNCTION_INCLUDED
#define N2O_CONVERTER_CONSTRUCTOR_FUNCTION_INCLUDED

#include <v8.h>

namespace n2o { namespace converter {

struct rvalue_from_js_stage1_data;
typedef void (*constructor_function)(v8::Handle<v8::Value> source, rvalue_from_js_stage1_data*);

}} // end of namespace converter, n2o

#endif // N2O_CONVERTER_CONSTRUCTOR_FUNCTION_INCLUDED
