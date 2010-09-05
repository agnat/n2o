#!/usr/bin/env node

var sys = require('sys'),
    bttf  = require('./binding');

sys.puts(sys.inspect(bttf));

bttf.greet();
sys.puts(bttf.int_f_void());

// vim: filetype=javascript :
