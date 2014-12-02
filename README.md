# N₂O - Node add-on's ala boost python

N₂O is a binding framework similar to boost python by David Abrahams et al.
It uses both, template and preprocessor metaprogramming techniques to do its
magic and, thus, is a major mess. It is far from complete and mostly
experimental but it is fun to play with. So, here we go...

> N₂O, Nitrous oxide, commonly known as lolgas – consumable by both, engines
> and humans. More horsepowers for V8, more fun for developers. So, don't
> become like Bill Clinton. Inhale!

#### hello.cpp:
````c++
#include <n2o.hpp>
#include <iostream>

using namespace n2o;

void greet() { std::cerr << "Hello world." << std::endl; }
int  add(int a, int b) { return a + b; }

N2O_ADD_ON(object exports) {
  exports["greet"] = function(greet);
  exports["add"]   = function(add);
}

````

#### hello.js:
````javascript
const hello = require('hello');

hello.greet();
console.log(hello.add(2, 3));
````
