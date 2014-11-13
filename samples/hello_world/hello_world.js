const root  = require('path').resolve(__dirname, '.')
    , hello = require('bindings')({ module_root: root, bindings: 'hello_world' });

hello.greet();
hello.add(2,3);
console.log(hello.five());
console.log(hello.hello());
