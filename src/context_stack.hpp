#ifndef N2O_CONTEXT_STACK_INCLUDED
#define N2O_CONTEXT_STACK_INCLUDED

#include <v8.h>

namespace n2o { namespace detail {


struct context_frame {
    context_frame(v8::Handle<v8::Object> const & ctx, context_frame * prev) :
        context(v8::Local<v8::Object>::New(ctx)),
        previous(prev)
    {
    }
    v8::Local<v8::Object>  context;
    context_frame *    previous;
};

// absolutly not thread safe and quite ugly ... but anyway
static context_frame * current_context(NULL);

v8::Local<v8::Object>
get_context() {
    return current_context->context;
}

class context_scope {
    public:
        context_scope(v8::Handle<v8::Object> ctx) {
            context_frame * previous = current_context;
            current_context = new context_frame(ctx, previous);
        }
        ~context_scope() {
            context_frame * previous = current_context->previous;
            delete current_context;
            current_context = previous;
        }
};

}} // end of namespace detail, n2o

#endif // N2O_CONTEXT_STACK_INCLUDED
