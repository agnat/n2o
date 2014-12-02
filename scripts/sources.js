#!/usr/bin/env node
require('glob')('+(n2o|src)/**/*.[ch]?(pp)', function(error, files) {
  files.unshift('n2o.hpp');
  console.log(files);  
});

