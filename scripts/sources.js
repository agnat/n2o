#!/usr/bin/env node
require('glob')('+(n2o|src)/**/*.[ch]pp', function(error, files) {
  console.log(files);  
});

