require('../..')
const root  = require('path').resolve(__dirname, '.')
    , sandbox = require('bindings')({ module_root: root, bindings: 'sandbox' });

sandbox.greet();
console.log(sandbox.five());
console.log(sandbox.hello());
sandbox.add(2,3);
