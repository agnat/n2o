#ifndef N2O_MODULE_HPP_INCLUDED_
#define N2O_MODULE_HPP_INCLUDED_

#include <node.h>

#include <n2o/object.hpp>

#define N2O_MODULE(args) N2O_NAMED_MODULE( N2O_MODULE_NAME, args )
#define N2O_NAMED_MODULE(name, args) \
  void n2o_init_ ## name(n2o::object object); \
  void n2o_node_init_ ## name(v8::Handle<v8::Object> o) { n2o_init_ ## name(object(o)); } \
  NODE_MODULE(name, n2o_node_init_ ## name); \
  void n2o_init_ ## name( args )


#endif // N2O_MODULE_HPP_INCLUDED_
