#include <n2o/js_type_info.hpp>

namespace n2o {

static js_type_info undefined_info("undefined");
static js_type_info boolean_info("boolean");
static js_type_info number_info("number");
static js_type_info string_info("string");
static js_type_info symbol_info("symbol");
static js_type_info function_info("function");
static js_type_info object_info("object");

char const*
js_type_info::name() const {
    return name_;
}

js_type_info const&
js_typeof(v8::Handle<v8::Value> v) {
    if (v->IsUndefined()) {
        return undefined_info;
    } else if (v->IsNull()) {
        return object_info;
    } else if (v->IsBoolean()) {
        return boolean_info;
    } else if (v->IsNumber()) {
        return number_info;
    } else if (v->IsString()) {
        return string_info;
    } else if (v->IsSymbol()) {
        return symbol_info;
    } else if (v->IsFunction()) {
        return function_info;
    }
    return object_info;
}

} // end of namespace n2o
