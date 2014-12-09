#!/usr/bin/env node

var n2o_test = require('../tools/lib/n2o_test')
  , path = require('path')
  , fs = require('fs')
  , test = require('tap').test
  , includeRegEx = /^\s*#\s*include\s*<([^>]+)>/
  ;


function testSettingsIncluded(file) {
  test(file + ' includes settings header', function (t) {
    t.plan(2);
    file = path.resolve(__dirname, '../', file);
    fs.readFile(file, function(error, src) {
      console.log(file, error);
      var includes = src . toString()
                         . split('\n')
                         . filter(function(l) { return l.match(includeRegEx) })
                         . map(function(l) { return l.replace(includeRegEx, "$1") })
                         ;
      t.strictEqual(includes[0], 'n2o/settings.hpp', file + ' includes settings header first');
      t.test('test includes are unique', function (t) {
        t.plan(includes.length);
        for (var i in includes) {
          var inc = includes[i];
          t.strictEqual(includes.indexOf(inc, i + 1), -1, file + ' includes ' + inc + ' only once');
        }
        t.end();
      });
      t.end();
    });
  });
}

n2o_test.headers(function(error, files) {
  for (var i in files) {
    if (files[i] != "n2o/settings.hpp") {
      testSettingsIncluded(files[i]);
    }
  }
});

// vim: syntax=javascript
