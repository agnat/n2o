#!/usr/bin/env node
require('../..'); // n2o;
const root  = require('path').resolve(__dirname, '.')
    , hello = require('bindings')({ module_root: root, bindings: 'hello_world' });

hello.greet();
