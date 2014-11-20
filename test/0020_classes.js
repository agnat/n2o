#!/usr/bin/env node

require('..')
const test  = require('tap').test
  , root    = require('path').resolve(__dirname, '.')
  , classes = require('bindings')({ module_root: root, bindings: 'classes' });

test("class hello world", function(t) {
  t.plan(4);

  t.type(classes.World, 'function');
  t.strictEquals(classes.World.name, 'World');
  t.type(new classes.World(), 'object');
  t.throws(function() { classes.World() }, "constructor called without 'new' must throw");
  console.log(classes.World);
  console.log(classes.World.prototype);
  console.log(classes.World.prototype.__proto__);
  var world = new classes.World();
  console.log(world);

  t.end();
});
