#ifndef N2O_INCLUDED
#define N2O_INCLUDED

#include <v8.h>

#include "context_stack.hpp"
#include "caller.hpp"

namespace n2o {

template <typename F>
void
function(const char * name, F f) {
    detail::get_context()->Set( v8::String::NewSymbol(name),
            v8::FunctionTemplate::New(detail::caller<F>::call)->GetFunction());
}

template <typename T>
struct class_ {
    class_(const char * classname) {}

    template <typename F>
    class_ &
    function(const char * name, F f) {
        return *this;
    }
};

} // end of namespace n2o

#define N2O_MODULE( module_name ) \
void init_ ## module_name (); \
extern "C" \
void init(v8::Handle<v8::Object> context) { \
    v8::HandleScope hscope; \
    n2o::detail::context_scope cscope(context); \
    init_ ## module_name(); \
} \
\
void init_ ## module_name ()

#endif // N2O_INCLUDED
