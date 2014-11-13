#!/bin/sh
node-gyp clean
node-gyp configure -- `node -e 'require("n2o")()'`
node-gyp build

