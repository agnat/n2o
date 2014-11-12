#include <n2o.hpp>

#include <iostream>

using namespace n2o;

void greet() { std::cerr << "hello world" << std::endl; }


void init(object exports) {

  exports["greet"] = function(greet);
}

N2O_MODULE(hello_world, init);

