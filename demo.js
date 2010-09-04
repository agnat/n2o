#!/usr/bin/env node

var sys = require('sys'),
    bttf  = require('./binding');

sys.puts(sys.inspect(bttf));

bttf.greet();

// vim: filetype=javascript :
