require('../..')
const root  = require('path').resolve(__dirname, '.')
    , sandbox = require('bindings')({ module_root: root, bindings: 'sandbox' });

sandbox.greet();
console.log(sandbox.five());
console.log(sandbox.hello());
var a = 2, b = 3;
console.log(a + ' + ' + b + ' = ' + sandbox.add(a, b));
try {
  sandbox.add("foo");
} catch (ex) {
  console.log(ex);
}

var world = new sandbox.World();


