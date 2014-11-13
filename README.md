# N₂O - Node add-on DSL ala boost::python

#### hello.cpp:
````c++
#include <iostream>
#include <n2o.hpp>

using namespace n2o;

void greet() { std::cerr << "Hello world." << std::endl; }

void init(object exports) {
  exports["greet"] = function(greet);
}

N2O_MODULE(init);

````

#### hello.js:
````javascript
const hello = require('hello');

hello.greet();
````
