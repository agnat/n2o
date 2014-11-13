#include <iostream>
#include <n2o.hpp>

using namespace n2o;

void greet() { std::cerr << "hello world" << std::endl; }

void init(object exports) {
  exports["greet"] = function(greet);
}

N2O_MODULE(init);
