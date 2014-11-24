#include <iostream>
#include <n2o.hpp>

using namespace n2o;

void greet() { std::cerr << "hello world" << std::endl; }
int  five() { return 5; }
char const* hello() { return "hello"; }
int  add(int a, int b) { return a + b; }

struct world {};

N2O_ADD_ON(object exports) {
  exports["greet"] = function(greet);
  exports["five"]  = function(five);
  exports["hello"] = function(hello);
  exports["add"]   = function(add);

  exports["World"] = class_<world>("World");
}
