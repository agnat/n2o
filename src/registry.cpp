#include <n2o/converter/registry.hpp>

#include <set>

#include <n2o/converter/registrations.hpp>
#include <n2o/converter/builtin_converters.hpp>

// Apple mach workaround
# include <iostream>

#define N2O_TRACE(x) // x
namespace n2o { namespace converter {

namespace {

typedef registration entry;
typedef std::set<entry> registry_t;

registry_t &
entries() {
    static registry_t registry;
    static bool builtin_converters_initialized = false;
    if ( ! builtin_converters_initialized) {
        builtin_converters_initialized = true;

        initialize_builtin_converters();
    }
    
    N2O_TRACE(
    std::cout << "registry: ";
    for (registry_t::iterator p = registry.begin(); p != registry.end(); ++p) {
        std::cout << p->target_type << "; ";
    }
    std::cout << std::endl;
    )
    return registry;
}

entry *
get(type_info type, bool is_shared_ptr = false) {
    N2O_TRACE(
    registry_t::iterator p = entries().find(entry(type));
    std::cout << "looking up " << type << ": " 
              << (p == entries().end() || p->target_type != type ?
                 "... NOT found" : "... found") << std::endl;
    )
    std::pair<registry_t::const_iterator, bool> pos_ins =
            entries().insert(entry(type, is_shared_ptr));
    return const_cast<entry*>(&*pos_ins.first);
}

} // end of anonymous namespace

namespace registry {

void
insert(to_js_function_t f, type_info source_t, js_type_info const* (*to_js_target_type)()) { 
    std::cout << "inserting to_js " << source_t << "\n";

    entry * slot = get(source_t);

    //assert(slot->to_js_ == 0);
    if (slot->to_js_ != 0) {
        std::string msg = std::string("to-JS converter for ") + source_t.name() +
                " already registered; second conversion method ignored.";
    
        std::cerr << msg << std::endl;

        //throw_error_already_set();
    }
    slot->to_js_ = f;
    slot->to_js_target_type_ = to_js_target_type;
}

void
insert(convertible_function convert, type_info key, js_type_info const* (*exp_js_type)()) {
    N2O_TRACE(std::cout << "inserting lvalue from_js " << key << std::endl;)
    entry * found = get(key);
    lvalue_from_js_chain * registration = new lvalue_from_js_chain;
    registration->convert = convert;
    registration->next = found->lvalue_chain;
    found->lvalue_chain = registration;

    insert(convert, 0, key, exp_js_type);
}

void
insert( convertible_function convertible
      , constructor_function construct
      , type_info key
      , js_type_info const* (*exp_js_type)())
{
    N2O_TRACE(std::cout << "inserting rvalue from_js " << key << std::endl;)

    entry* found = get(key);
    rvalue_from_js_chain * registration = new rvalue_from_js_chain;
    registration->convertible = convertible;
    registration->construct = construct;
    registration->expected_js_type = exp_js_type;
    registration->next = found->rvalue_chain;
    found->rvalue_chain = registration;
}

void
push_back( convertible_function convertible
         , constructor_function construct
         , type_info key
         , js_type_info const* (*exp_js_type)())
{
    N2O_TRACE(std::cout << "push_back rvalue from_js " << key << std::endl;)

    rvalue_from_js_chain** found = &get(key)->rvalue_chain;
    while (*found != 0) {
        found = &(*found)->next;
    }

    rvalue_from_js_chain * registration = new rvalue_from_js_chain;
    registration->convertible = convertible;
    registration->construct = construct;
    registration->expected_js_type = exp_js_type;
    registration->next = 0;
    *found = registration;
}

registration const& lookup(type_info key) {
    return *get(key);
}

registration const& lookup_shared_ptr(type_info key) {
    return *get(key, true);
}

registration const* query(type_info key) {
    registry_t::iterator p = entries().find(entry(key));
    std::cout << "querying" << key << ((p == entries().end() || p->target_type != key) ?
            "... NOT found" : "... found") << std::endl;
    return (p == entries().end() || p->target_type != key) ? 0 : &*p;
}

} // end of namespace registry

}} // end of namespace n2o::converter
