#include <n2o/converter/builtin_converters.hpp>

#include <boost/cast.hpp>

#include <n2o/converter/rvalue_from_js_data.hpp>
#include <n2o/converter/registry.hpp>
#include <n2o/type_id.hpp>


namespace n2o { namespace converter {

typedef v8::Handle<v8::Value> (*unaryfunc)(v8::Handle<v8::Value>);

namespace {

template <typename T, typename SlotPolicy>
struct slot_rvalue_from_js {
    slot_rvalue_from_js() {
        registry::insert(
                  & slot_rvalue_from_js<T, SlotPolicy>::convertible
                , & slot_rvalue_from_js<T, SlotPolicy>::construct
                , n2o::type_id<T>() // XXX why the namespace?
                , & SlotPolicy::get_jstype
                );
    }
private:
    static void* convertible(v8::Handle<v8::Value> v) {
        unaryfunc * slot = SlotPolicy::get_slot(v);
        return slot && *slot ? slot : 0;
    }
    static void construct(v8::Handle<v8::Value> v, rvalue_from_js_stage1_data* data) {
        unaryfunc creator = * static_cast<unaryfunc*>(data->convertible);
        v8::Local<v8::Value> intermediate = creator(v);

        void * storage = ((rvalue_from_js_storage<T>*)data)->storage.bytes;

        new (storage) T(SlotPolicy::extract(intermediate));

        // record successful construction
        data->convertible = storage;
    }
};

v8::Handle<v8::Value> identity_unaryfunc(v8::Handle<v8::Value> x) {
    return x;
}

unaryfunc js_value_identity = identity_unaryfunc;

struct int_rvalue_from_js_base {
    static unaryfunc* get_slot(v8::Handle<v8::Value> v) {
        return v->IsInt32() || v->IsUint32() ? &js_value_identity : 0; // XXX
    }
    static js_type_info const* get_jstype() { return 0; }
};

template <typename T>
struct signed_int_rvalue_from_js : int_rvalue_from_js_base {
    static T extract(v8::Handle<v8::Value> intermediate) {
        int64_t x = intermediate->IntegerValue();
        return boost::numeric_cast<T>(x);
    }
};

template <typename T>
struct unsigned_int_rvalue_from_js : int_rvalue_from_js_base {
    static T extract(v8::Handle<v8::Value> intermediate) {
        int64_t x = intermediate->IntegerValue();
        return boost::numeric_cast<T>(x);
    }
};

struct bool_rvalue_from_js {
    static unaryfunc* get_slot(v8::Handle<v8::Value> v) {
        return v->IsBoolean() ? & js_value_identity : 0;
    }
    static bool extract(v8::Handle<v8::Value> v) {
        return v->BooleanValue();
    }
    static js_type_info const* get_jstype() { return 0; }
};

} // end of anonymous namespace

v8::Local<v8::Value>
do_return_to_js(char x) {
    return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), &x ,v8::String::kNormalString, 1);
}

v8::Local<v8::Value>
do_return_to_js(char const* x) {
    if (x) {
        return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), x ,v8::String::kNormalString);
    }
    return v8::Undefined(v8::Isolate::GetCurrent());
}

v8::Local<v8::Value>
do_return_to_js(v8::Handle<v8::Value> x) {
    if ( ! x.IsEmpty()) {
        return x;
    }
    return v8::Undefined(v8::Isolate::GetCurrent());
}

#define REGISTER_INT_CONVERTERS_S(signedness, U)               \
    slot_rvalue_from_js<                                       \
              signedness U                                     \
            , signedness ## _int_rvalue_from_js<signedness U>  \
    >()

#define REGISTER_INT_CONVERTERS(U)        \
    REGISTER_INT_CONVERTERS_S(signed, U); \
    REGISTER_INT_CONVERTERS_S(unsigned, U)

void
initialize_builtin_converters() {
    // booleans
    slot_rvalue_from_js<bool, bool_rvalue_from_js>();

    // integers
    REGISTER_INT_CONVERTERS(char);
    REGISTER_INT_CONVERTERS(short);
    REGISTER_INT_CONVERTERS(int);
    REGISTER_INT_CONVERTERS(long);
}

}} // end of namespace n2o::converter
