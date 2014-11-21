#!/usr/bin/env node

require('..')
const test     = require('tap').test
  , root       = require('path').resolve(__dirname, '.')
  , exceptions = require('bindings')({ module_root: root, bindings: 'exceptions' });

test('standard exceptions', function(t) {
  t.plan(6);

  t.type(exceptions.throw_bad_alloc, 'function');
  t.throws(exceptions.throw_bad_alloc);

  t.type(exceptions.throw_bad_numeric_cast, 'function');
  t.throws(exceptions.throw_bad_numeric_cast);

  t.type(exceptions.throw_out_of_range, 'function');
  t.throws(exceptions.throw_out_of_range);

  t.end();
});

test('exception in module init', function(t) {
  t.plan(1);
  t.throws(function() {
    require('bindings')({ module_root: root, bindings: 'init_except' });
  });
  t.end();
});
