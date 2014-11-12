#ifndef N2O_CONVERTER_REGISTRY_INCLUDED
#define N2O_CONVERTER_REGISTRY_INCLUDED

#include "convertible_function.hpp"
#include "to_js_function_type.hpp"
#include "../type_id.hpp"

namespace n2o { namespace converter {

struct registration;

namespace registry {

registration const& lookup(type_info);
registration const& lookup_shared_ptr(type_info);

registration const* query(type_info);

void insert(to_js_function_t, type_info/*, js_type_info const* (*to_js_target_type)() = 0*/);

void insert(convertible_function, type_info/*, js_type_info const* (*expected_js_type)() = 0*/);

void insert(
          convertible_function
        , constructor_function
        , type_info
        //, js_type_info const* (*expected_js_type)() = 0
        );

void push_back(
          convertible_function
        , constructor_function
        , type_info
        //, js_type_info const* (*expected_js_type)() = 0
        );

} // end of namespace registry


}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_REGISTRY_INCLUDED
