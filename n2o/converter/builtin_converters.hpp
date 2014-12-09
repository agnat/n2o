//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONVERTER_BUILTIN_CONVERTER_INCLUDED
# define N2O_CONVERTER_BUILTIN_CONVERTER_INCLUDED

# include <n2o/settings.hpp>

# include <string>
# include <v8.h>

# include <n2o/js_type_info.hpp>

namespace n2o {

namespace converter {
    template <typename T> struct arg_to_js;
    v8::Local<v8::Value> do_return_to_js(char);
    v8::Local<v8::Value> do_return_to_js(char const*);
    v8::Local<v8::Value> do_return_to_js(v8::Handle<v8::Value>);
    v8::Local<v8::Value> do_arg_to_js(v8::Handle<v8::Value>);
} // end of namespace converter

template <typename T> struct to_js_value;

namespace detail {
    struct builtin_to_js { static const bool uses_registry = false; };
}


# define N2O_RETURN_TO_JS_BY_VALUE(T, expr, jstype)                    \
    template <> struct to_js_value<T&> : detail::builtin_to_js {       \
        inline v8::Local<v8::Value> operator()(T const& x) const {     \
            return (expr);                                             \
        }                                                              \
        inline js_type_info const* get_jstype() const {                \
            return (jstype);                                           \
        }                                                              \
    };                                                                 \
    template <> struct to_js_value<T const&> : detail::builtin_to_js { \
        inline v8::Local<v8::Value> operator()(T const& x) const {     \
            return (expr);                                             \
        }                                                              \
        inline js_type_info const* get_jstype() const {                \
            return (jstype);                                           \
        }                                                              \
    };

# define N2O_ARG_TO_JS_BY_VALUE(T, expr)              \
    namespace converter {                             \
        template <> struct arg_to_js<T>{              \
            arg_to_js(T const& x) {}                  \
        };                                            \
    }

# define N2O_TO_JS_BY_VALUE(T, expr, jstype)    \
    N2O_RETURN_TO_JS_BY_VALUE(T, expr, jstype)  \
    N2O_ARG_TO_JS_BY_VALUE(T, expr)

# define N2O_TO_INT(T)                                                               \
    N2O_TO_JS_BY_VALUE(signed T, v8::Integer::New(v8::Isolate::GetCurrent(), x), 0)  \
    N2O_TO_JS_BY_VALUE(unsigned T, v8::Integer::NewFromUnsigned(v8::Isolate::GetCurrent(), x), 0)

N2O_TO_JS_BY_VALUE(bool, v8::Boolean::New(v8::Isolate::GetCurrent(), x), 0)

N2O_TO_INT(char)

N2O_TO_INT(short)
N2O_TO_INT(int)
//N2O_TO_INT(long)
N2O_TO_JS_BY_VALUE(long, v8::Number::New(v8::Isolate::GetCurrent(), x), 0)


N2O_TO_JS_BY_VALUE(char, converter::do_return_to_js(x), 0)
N2O_TO_JS_BY_VALUE(char const*, converter::do_return_to_js(x), 0)
N2O_TO_JS_BY_VALUE( std::string
                  , v8::String::NewFromUtf8( v8::Isolate::GetCurrent()
                                           , x.data()
                                           , v8::String::kNormalString
                                           , static_cast<int>(x.size()))
                  , 0)

N2O_TO_JS_BY_VALUE(float, v8::Number::New(v8::Isolate::GetCurrent(), x), 0)
N2O_TO_JS_BY_VALUE(double, v8::Number::New(v8::Isolate::GetCurrent(), x), 0)

# undef N2O_RETURN_TO_JS_BY_VALUE
# undef N2O_ARG_TO_JS_BY_VALUE
# undef N2O_TO_JS_BY_VALUE
# undef N2O_TO_INT

namespace converter {
    void initialize_builtin_converters();
}

} // end of namespace n2o

#endif // N2O_CONVERTER_BUILTIN_CONVERTER_INCLUDED
