#ifndef N2O_INCLUDED
#define N2O_INCLUDED

#include "config.h"

#include <v8.h>

#include "invoke.hpp"
#include "signature.hpp"

#include "function.hpp"
#include "class.hpp"

#include "context_stack.hpp"

#define N2O_NODE_MODULE( init_func ) \
void init_ ## module_name (); \
extern "C" \
void init(v8::Handle<v8::Object> context) { \
    v8::HandleScope hscope; \
    n2o::detail::context_scope cscope(context); \
    init_func(); \
} \

#endif // N2O_INCLUDED
