#!/usr/bin/env node

require('..')
const test     = require('tap').test
  , root       = require('path').resolve(__dirname, '.')
  , exceptions = require('bindings')({ module_root: root, bindings: 'exceptions' });

test('exception in module init', function(t) {
  t.plan(1);
  t.throws(function() {
    require('bindings')({ module_root: root, bindings: 'init_except' });
  });
  t.end();
});
