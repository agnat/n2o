require('..')
const test    = require('tap').test
  , root      = require('path').resolve(__dirname, '.')
  , functions = require('bindings')({ module_root: root, bindings: 'functions' });

test('simple functions', function (t) {
  t.plan(11);

  t.type(functions.void_void, 'function');
  t.type(functions.void_void(), 'undefined');

  t.type(functions.void_int, 'function');
  t.type(functions.void_int(5), 'undefined');
  t.throws(function () { functions.void_int(/* missing */) });

  t.type(functions.int_void, 'function');
  t.type(functions.int_void(), 'number');

  t.type(functions.int_int, 'function');
  t.type(functions.int_int(5), 'number');
  t.strictEquals(functions.int_int(5), 5);
  t.throws(function () { functions.int_int(/* missing */) });

  t.end();
});


test('rvalue arguments', function (t) {
  t.plan(10);

  t.type(functions.bool_bool, 'function');
  t.type(functions.bool_bool(true), 'boolean');
  t.strictEquals(functions.bool_bool(true), true);
  t.strictEquals(functions.bool_bool(false), false);

  t.type(functions.signed_char_short_int_long, 'function');
  t.type(functions.signed_char_short_int_long(1,1,1,1), 'number');
  t.strictEquals(functions.signed_char_short_int_long(-1,-1,-1,-1), -4);

  t.type(functions.unsigned_char_short_int_long, 'function');
  t.type(functions.unsigned_char_short_int_long(1,1,1,1), 'number');
  t.strictEquals(functions.unsigned_char_short_int_long(1,1,1,1), 4);

  t.end();
});
