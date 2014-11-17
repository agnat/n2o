const test = require('tap').test
    , spawn = require('child_process').spawn
    ;

test('build test add-ons', function(t) {
  t.plan(1);
  spawn('node-gyp', ['rebuild'], { 'cwd': __dirname, 'stdio': 'inherit'})
    . on('close', function(code) { t.strictEqual(code, 0); t.end();})
    ;
});
