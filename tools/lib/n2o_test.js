var path = require('path')
  , fs   = require('fs')
  , child_process = require('child_process')
  , temp = require('temp')
  , merge = require('merge')
  , slide = require('slide')
  , glob = require('glob')
  , chain = slide.chain
  , asyncMap = slide.asyncMap
  ;

temp.track();

exports.compile = function compile(code, options, callback) {
  temp.mkdir('node-configure', function(error, directory) {
    if (error) { return callback(error) }
    var configOpts = {cwd: directory, stdio: 'ignore' }
      , buildOpts = {cwd: directory, stdio: ['ignore', 'ignore', process.stderr] }
      , test =  path.join('build', 'Release', 'test');
    chain( [ [ writeProjectFiles, directory, code, 'executable', options ]
           , [ spawn, 'node-gyp', ['configure'], configOpts ]
           , [ spawn, 'node-gyp', ['build', '--loglevel=warn'], buildOpts ]
           , [ spawn, test, [], configOpts ]
           ], callback);

  });
}

exports.headers = function headers(callback) {
  var root = path.resolve(__dirname, '../..');
  glob(path.join(root, 'n2o/**/*.h?(pp)'), function(error, files) {
    files = files.map(function(f){ return path.relative(root, f) });
    files.unshift('n2o.hpp');
    callback(error, files);
  });
}

function writeProjectFiles(dir, code, type, options, callback) {
  var gyp = JSON.stringify(targetGyp("test", ["test.cpp"], type, options), null, 2) + '\n'
    , files = [ { name: path.join(dir, "test.cpp"), content: code }
              , { name: path.join(dir, "binding.gyp"), content: gyp }
              ];
  asyncMap( files
          , function(file, cb) { fs.writeFile(file.name, file.content, cb) }
          , callback);
}

function targetGyp(name, sources, type, options) {
  var gyp =
      { 'targets': [
        { 'target_name': name
        , 'type': type || 'executable' 
        , 'sources': sources
        , 'conditions': [['OS=="mac"', {'libraries!': ['-undefined dynamic_lookup']}]]
        }
      ]}
    gyp.targets[0] = merge(gyp.targets[0], options);
    return gyp;
}

function spawn(executable, args, options, callback) {
  if ( ! callback) {
    callback = options;
    options = { stdio: 'ignore' };
  }
  child_process.spawn(executable, args, options).on('close', function (code) {
    callback(code
      ? new Error(executable + ' ' + args.join(' ') + ' failed: ' + code)
      : undefined
      );
  });
}

