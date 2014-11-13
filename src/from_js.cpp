#include "from_js.hpp"

namespace n2o { namespace converter {


rvalue_from_js_stage1_data
rvalue_from_js_stage1(v8::Handle<v8::Value> source, registration const& converters) {
    rvalue_from_js_stage1_data data;
    //data.convertible = objects::find_instance_impl(source, converters.target_type, converters.is_shared_ptr);
    if (data.convertible) {
        data.construct = NULL;
    } else {
        for (rvalue_from_js_chain const * chain = converters.rvalue_chain;
                chain != NULL;
                chain = chain->next)
        {
            void * r = chain->convertible(source);
            if (r != 0) {
                data.convertible = r;
                data.construct = chain->construct;
                break;
            }
        }
    }
    return data;
}

}} // end of namespace converter, n2o
