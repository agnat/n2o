#ifndef N2O_MODULE_HPP_INCLUDED_
#define N2O_MODULE_HPP_INCLUDED_

#include <boost/bind.hpp>
#include <node.h>

#include <n2o/object.hpp>

#define N2O_MODULE(args) N2O_NAMED_MODULE( N2O_MODULE_NAME, args )

#define N2O_NAMED_MODULE(name, args)                                          \
    void n2o_init_ ## name(args);                                             \
    void n2o_node_init_ ## name(v8::Handle<v8::Object> exports) {             \
        v8::HandleScope scope(v8::Isolate::GetCurrent());                     \
        n2o::handle_exception(                                                \
                boost::bind(n2o_init_ ## name, n2o::object(exports)));        \
    }                                                                         \
    NODE_MODULE(name, n2o_node_init_ ## name);                                \
    void n2o_init_ ## name( args )

#endif // N2O_MODULE_HPP_INCLUDED_
