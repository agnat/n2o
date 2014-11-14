#include <iostream>
#include <n2o.hpp>

using namespace n2o;

void greet() { std::cerr << "hello world" << std::endl; }
void add(int a, int b) { std::cerr << a << " + " << b << " = " << a + b << std::endl; }
int  five() { return 5; }
char const* hello() { return "hello"; }


void init(object exports) {
  exports["greet"] = function(greet);
  exports["add"]   = function(add);
  exports["five"]  = function(five);
  exports["hello"] = function(hello);
}

N2O_MODULE(init);
