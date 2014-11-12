# N₂O - Node add-on DSL ala boost python

### hello.cpp:
````c++
void greet() { std::cerr << "Hello world." << std::endl; }

void init(object exports) {
  exports["greet"] = function(greet);
}

N2O_MODULE(hello, init);

````

### hello_world.js:
````javascript
const hello = require('hello');

hello.greet();
````
