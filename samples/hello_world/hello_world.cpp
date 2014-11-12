#include <nil.hpp>

#include <iostream>

using namespace nil;

namespace {

void greet() {
  std::cerr << "hello world" << std::endl;
}

void init(object exports) {

  exports["greet"] = function(greet);
}

NIL_MODULE(hello_world, init);

}

