#ifndef N2O_CONVERTER_FROM_JS_INCLUDED
#define N2O_CONVERTER_FROM_JS_INCLUDED

#include <n2o/converter/rvalue_from_js_data.hpp>
#include <n2o/converter/convertible_function.hpp>

namespace n2o { namespace converter {

// TODO:
struct rvalue_from_js_chain {
    convertible_function convertible;
    constructor_function construct;
    rvalue_from_js_chain * next;
};

// TODO:
struct registration {
    rvalue_from_js_chain * rvalue_chain;
};

rvalue_from_js_stage1_data
rvalue_from_js_stage1(v8::Handle<v8::Value>, registration const&);

}} // end of namespace converter, n2o

#endif // N2O_CONVERTER_FROM_JS_INCLUDED

