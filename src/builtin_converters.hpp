#ifndef N2O_BUILTIN_CONVERTERS_INCLUDED
#define N2O_BUILTIN_CONVERTERS_INCLUDED

namespace n2o {

namespace detail {
    struct builtin_to_v8 {};
}

template <class T> struct to_v8_value;

#define N2O_RETURN_TO_V8_BY_VALUE(T, expr) \
    template <> \
    struct to_v8_value<T&> : detail::builtin_to_v8 { \
        inline \
        v8::Handle<v8::Value> \
        operator()(T const& v) const { \
            return (expr); \
        } \
    }; \
    template <> \
    struct to_v8_value<T const&> : detail::builtin_to_v8 { \
        inline \
        v8::Handle<v8::Value> \
        operator()(T const& v) const { \
            return (expr); \
        } \
    };

#define N2O_TO_V8_BY_VALE(T, expr) \
    N2O_RETURN_TO_V8_BY_VALUE(T, expr)


#define N2O_TO_INT(T) \
    N2O_TO_V8_BY_VALE( signed T, v8::Integer::New(v8::Isolate::GetCurrent(), v )) \
    N2O_TO_V8_BY_VALE( unsigned T, v8::Integer::NewFromUnsigned(v8::Isolate::GetCurrent(), v ))

// handles signed char and unsigned char but not char
N2O_TO_INT( char )
N2O_TO_INT( short )
N2O_TO_INT( int )

} // end of namespace n2o

#endif // N2O_BUILTIN_CONVERTERS_INCLUDED
