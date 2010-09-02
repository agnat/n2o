#ifndef N2O_FUNCTION_WRAPPER_INCLUDED
#define N2O_FUNCTION_WRAPPER_INCLUDED

namespace n2o { namespace detail {

template <typename F>
struct caller {
    static
    v8::Handle<v8::Value>
    call(v8::Arguments const& args) {
    }
};

}} // end of namespace detail, n2o

#endif // N2O_FUNCTION_WRAPPER_INCLUDED
