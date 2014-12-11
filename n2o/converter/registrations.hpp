//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_REGISTRATIONS_INCLUDED
# define N2O_CONVERTER_REGISTRATIONS_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/converter/convertible_function.hpp>
# include <n2o/converter/constructor_function.hpp>
# include <n2o/js_type_info.hpp>
# include <n2o/type_id.hpp>
# include <n2o/converter/to_js_function_type.hpp>

namespace n2o { namespace converter {

struct lvalue_from_js_chain {
    convertible_function   convert;
    lvalue_from_js_chain * next;
};

struct rvalue_from_js_chain {
    convertible_function   convertible;
    constructor_function   construct;
    js_type_info const*  (*expected_js_type)();
    rvalue_from_js_chain * next;
};

struct registration {
    explicit registration(type_info target, bool is_shared_ptr = false);
    ~registration();
    
    v8::Handle<v8::Value> to_js(void const volatile*) const;
    
    js_type_info * get_type_object() const;

    js_type_info const* expected_from_js_type() const;
    js_type_info const* to_js_target_type() const;

    const n2o::type_info target_type;

    lvalue_from_js_chain * lvalue_chain;
    rvalue_from_js_chain * rvalue_chain;

    js_type_info * type_object_;

    to_js_function_t to_js_;
    js_type_info const* (*to_js_target_type_)();

    const bool is_shared_ptr;
};

inline
registration::registration(type_info target_type, bool is_shared_ptr)
    : target_type(target_type)
    , lvalue_chain(0)
    , rvalue_chain(0)
    , type_object_(0)
    , to_js_(0)
    , to_js_target_type_(0)
    , is_shared_ptr(is_shared_ptr)
{}

inline bool operator<(registration const& lhs, registration const& rhs) {
    return lhs.target_type < rhs.target_type;
}

}} // end of namespace n2o::converter

#endif // N2O_CONVERTER_REGISTRATIONS_INCLUDED
