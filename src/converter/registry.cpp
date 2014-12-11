//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o/converter/registry.hpp>

#include <set>

#include <n2o/converter/registrations.hpp>
#include <n2o/converter/builtin_converters.hpp>
#include <n2o/errors.hpp>

// Apple mach workaround
#include <iostream>

#define N2O_TRACE(x) // x
namespace n2o { namespace converter {

js_type_info const*
registration::expected_from_js_type() const {
    if (this->type_object_ != 0) {
        return this->type_object_;
    }

    std::set<js_type_info const*> pool;

    for (rvalue_from_js_chain * r = rvalue_chain; r; r=r->next) {
        if (r->expected_js_type) {
            pool.insert(r->expected_js_type());
        }
    }

    // for now D.Abrahams skips the search for a common base ;)
    if (pool.size() == 1) {
        return *pool.begin();
    }

    return 0;
}

js_type_info const*
registration::to_js_target_type() const {
    if (this->type_object_ != 0) {
        return this->type_object_;
    }

    if (this->to_js_target_type_ != 0) {
        return this->to_js_target_type_();
    }

    return 0;
}

js_type_info *
registration::get_type_object() const {
    if (this->type_object_ == 0) {
        js_error( (std::string("no javascript class registered for c++ class ") 
                + this->target_type.name()).c_str());
        throw_error_already_set();
    }

    return this->type_object_;
}

v8::Handle<v8::Value>
registration::to_js(void const volatile* src) const {
    if (this->to_js_ == 0) {
        js_error( (std::string("no to_js (by-value) converter found for c++ type ")
                + this->target_type.name()).c_str());
        throw_error_already_set();
    }
    return src == 0 
        ? v8::Handle<v8::Value>(v8::Undefined(v8::Isolate::GetCurrent()))
        : this->to_js_(const_cast<void*>(src));
}

namespace {
    template <typename T>
    void
    delete_node(T* node) {
        if (not not node && not not node->next) {
            delete_node(node->next);
        }
        delete node;
    }
}

registration::~registration() {
    delete_node(lvalue_chain);
    delete_node(rvalue_chain);
}

namespace {

typedef registration entry;
typedef std::set<entry> registry_t;

registry_t &
entries() {
    static registry_t registry;
    static bool builtin_converters_initialized = false;
    if (not builtin_converters_initialized) {
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
