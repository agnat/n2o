# N₂O - Node add-on's ala boost python

> N₂O, Nitrous oxide, commonly known as lolgas – consumable by both, engines
> and humans. More horsepowers for V8, more fun for developers. So, don't
> become like Bill Clinton. Inhale!

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
