#!/usr/bin/env node
const test  = require('tap').test
    , spawn = require('child_process').spawn
    , path  = require('path')
    , fs    = require('fs')
    ;

test('build test add-ons', function(t) {
  t.plan(1);

  fs.exists(path.resolve(__dirname, 'build', 'Makefile'), function(exists) {
    var command = exists ? 'build' : 'rebuild';
    console.log(command);
    spawn('node-gyp', [command], { 'cwd': __dirname, 'stdio': 'inherit'})
      . on('close', function(code) { t.strictEqual(code, 0); t.end();})
      ;
  });
});
