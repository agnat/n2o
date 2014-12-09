//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_TAP_INCLUDED
# define N2O_TAP_INCLUDED

# include <string>
# include <vector>

# include <node.h>

# include <n2o/type_id.hpp>

namespace n2o {

inline
v8::Handle<v8::Value>
number(unsigned v) {
    return v8::Integer::NewFromUnsigned(v8::Isolate::GetCurrent(), v);
}

inline
v8::Handle<v8::Value>
boolean(bool v) {
    return v8::Boolean::New(v8::Isolate::GetCurrent(), v);
}

inline
v8::Handle<v8::Value>
string(char const* v) {
    return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), v);
}

template <typename T, typename U>
struct is_same {
  static const bool value = false;
};

template <typename T>
struct is_same<T, T> {
  static const bool value = true;
};

class tap {
    typedef std::vector<v8::Handle<v8::Value> > arguments_t;
public:
    explicit inline
    tap(v8::Handle<v8::Value> v) : t_(v8::Isolate::GetCurrent(), v.As<v8::Object>()) {};

    inline void plan(unsigned count) {
        arguments_t args;
        args.push_back(number(count));
        call("plan", args);
    }
    inline void end() { call("end"); }

    inline void ok(bool isOk, char const* message = 0) {
        arguments_t args;
        args.push_back(boolean(isOk));
        if (message) {
            args.push_back(string(message));
        }
        call("ok", args);
    }
    inline void ok(bool isOk, std::string const& message) {
        ok(isOk, message.c_str());
    }

    template <typename A, typename B>
    void
    type(B b) {
        ok(is_same<A, B>::value, std::string("type is ") + n2o::type_id<A>().name());
    }
private:

    inline
    void
    call(char const* symbol, std::vector<v8::Handle<v8::Value> > const& args = arguments_t()) {
        v8::Local<v8::Object> obj = v8::Local<v8::Object>::New(v8::Isolate::GetCurrent(), t_);
        v8::Local<v8::String> sym = string(symbol).As<v8::String>();
        node::MakeCallback(v8::Isolate::GetCurrent(), obj, sym, static_cast<int>(args.size()),
                const_cast<v8::Handle<v8::Value>*>(&*args.begin())); // XXX const correctness :-/
    }

    v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object> > t_;
};

} // end of namespace n2o
#endif // N2O_TAP_INCLUDED
