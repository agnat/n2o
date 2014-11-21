#!/usr/bin/env node

require('..')
const test     = require('tap').test
  , root       = require('path').resolve(__dirname, '.')
  , exceptions = require('bindings')({ module_root: root, bindings: 'exceptions' });

test('standard exceptions', function(t) {
  t.plan(6);

  t.type(exceptions.throw_bad_alloc, 'function');
  t.throws(exceptions.throw_bad_alloc, new Error('memory allocation failed'));

  t.type(exceptions.throw_bad_numeric_cast, 'function');
  t.throws(exceptions.throw_bad_numeric_cast,
    new RangeError('bad numeric conversion: negative overflow'));

  t.type(exceptions.throw_out_of_range, 'function');
  t.throws(exceptions.throw_out_of_range, new RangeError('kaputt'));

  t.end();
});

test('custom exception translator', function(t) {
  t.plan(3);

  t.type(exceptions.throw_out_of_cheese, 'function');
  t.throws(exceptions.throw_out_of_cheese, new Error('unknown c++ exception'));

  exceptions.register_translator();

  t.throws(exceptions.throw_out_of_cheese, new Error('out of cheese'));

  t.end();
});

test('exception in module init', function(t) {
  t.plan(1);
  t.throws(function() {
    require('bindings')({ module_root: root, bindings: 'init_except' });
  });
  t.end();
});
