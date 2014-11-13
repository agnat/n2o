#ifndef N2O_MODULE_HPP_INCLUDED_
#define N2O_MODULE_HPP_INCLUDED_

#include <node.h>

#include <n2o/object.hpp>

#define N2O_MODULE(init) N2O_NAMED_MODULE( N2O_MODULE_NAME, init )
#define N2O_NAMED_MODULE(name, init) \
  void n2o_init_ ## name(v8::Handle<v8::Object> o) { init(object(o)); } \
  NODE_MODULE(name, n2o_init_ ## name)


#endif // N2O_MODULE_HPP_INCLUDED_
