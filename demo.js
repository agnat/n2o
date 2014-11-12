#!/usr/bin/env node

var sys = require('sys'),
    bttf  = require('./binding');

sys.puts(sys.inspect(bttf));

bttf.greet();
sys.puts(bttf.int_f_void());
sys.puts(bttf.int_f_int(42));
sys.puts(bttf.int_f_int(5));
sys.puts(bttf.FluxCompensator);

var fc = new bttf.FluxCompensator();

// vim: filetype=javascript :
