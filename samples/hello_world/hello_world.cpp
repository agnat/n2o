//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o.hpp>
#include <iostream>

using namespace n2o;

void greet() { std::cerr << "hello world" << std::endl; }

N2O_ADD_ON(object exports) {
  exports["greet"] = function(greet);
}
