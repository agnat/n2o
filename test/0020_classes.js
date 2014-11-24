#!/usr/bin/env node

require('..')
const test  = require('tap').test
  , root    = require('path').resolve(__dirname, '.')
  , classes = require('bindings')({ module_root: root, bindings: 'classes' });

test("class hello world", function(t) {
  t.plan(9);

  t.type(classes.World, 'function');
  t.strictEquals(classes.World.name, 'World');
  t.type(new classes.World(), 'object');
  t.throws(classes.World, 'constructor called without "new" must throw');

  t.ok((new classes.World()) instanceof classes.World);
  t.strictEquals((new classes.World()).__proto__, classes.World.prototype);
  t.ok('greet' in classes.World.prototype);
  t.type(classes.World.prototype['greet'], 'function');
  t.ok('greet' in new classes.World());

  t.end();
});
