#!/usr/bin/env node

require('..');

var test = require('tap').test
  , root      = require('path').resolve(__dirname, '.')
  , path      = require('path')
  , type_info = process.env.__XCODE_BUILT_PRODUCTS_DIR_PATHS
              ? require(path.join(process.env.__XCODE_BUILT_PRODUCTS_DIR_PATHS, 'js_type_info'))
              : require('bindings')({ module_root: root, bindings: 'js_type_info' })  
  ;

for (var symbol in type_info) {
  if (typeof type_info[symbol] == 'function' && symbol.match(/^test_/)) {
    test('c++ ' + symbol, type_info[symbol]);
  }
}

