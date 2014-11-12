#ifndef N2O_MODULE_HPP_INCLUDED_
#define N2O_MODULE_HPP_INCLUDED_

#include <node.h>

#include "object.hpp"

#define N2O_MODULE(name, init) \
  void n2o_init_ ## name(v8::Handle<v8::Object> o) { init(object(o)); } \
  NODE_MODULE(name, n2o_init_ ## name)

#endif // N2O_MODULE_HPP_INCLUDED_
