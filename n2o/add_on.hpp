//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_ADD_ON_HPP_INCLUDED_
# define N2O_ADD_ON_HPP_INCLUDED_

# include <boost/bind.hpp>
# include <node.h>

# include <n2o/object.hpp>

# define N2O_ADD_ON(args) N2O_NAMED_ADD_ON( N2O_ADD_ON_NAME, args )

# define N2O_NAMED_ADD_ON(name, args)                                         \
    void n2o_init_ ## name(args);                                             \
    void n2o_node_init_ ## name( v8::Handle<v8::Object> exports               \
                               , v8::Handle<v8::Value> module                 \
                               , v8::Handle<v8::Context> context)             \
    {                                                                         \
        /* Although, node holds a scope in dlopen we want our own. */         \
        v8::HandleScope scope(context->GetIsolate());                         \
        n2o::handle_exception(                                                \
                boost::bind(n2o_init_ ## name, n2o::object(exports)));        \
    }                                                                         \
    NODE_MODULE_CONTEXT_AWARE(name, n2o_node_init_ ## name);                  \
    void n2o_init_ ## name( args )

#endif // N2O_ADD_ON_HPP_INCLUDED_
