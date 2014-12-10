#!/usr/bin/env node

var n2o_test = require ('../tools/lib/n2o_test')
  , path = require('path')
  , test = require('tap').test
  , opts = { includes: [path.resolve(__dirname, '../n2o.gypi')]}
  , excludes = ['n2o/value_call.hpp']
  ;

function compileSingleHeader(file) {
    test( file + " is self contained", function (t) {
      t.plan(1);
      var src = "#include <" + file + ">\n" +
                "int main() { return 0; }"
        ;
      n2o_test.compile(src, opts, function (error) {
        t.ok(!error, file + " is self contained");
        t.end();
      });
    });
}
n2o_test.headers(function(error, files) {
  for (var i in files) {
    if (excludes.indexOf(files[i]) == -1) {
      compileSingleHeader(files[i]);
    }
  }
});
