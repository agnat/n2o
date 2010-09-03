#!/usr/bin/env node

var sys = require('sys'),
    hw  = require('./lib/hello_world');

sys.puts(sys.inspect(hw));

hw.greet();

// vim: filetype=javascript :
