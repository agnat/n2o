#include <iostream>
#include <n2o.hpp>

using namespace n2o;

void greet() { std::cerr << "hello world" << std::endl; }

N2O_MODULE(object exports) {
  exports["greet"] = function(greet);
}
