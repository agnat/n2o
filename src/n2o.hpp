#ifndef N2O_INCLUDED
#define N2O_INCLUDED

#include "config.h"

#include <v8.h>

#include "signature.hpp"

#include "function.hpp"
#include "class.hpp"

#include "context_stack.hpp"

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
