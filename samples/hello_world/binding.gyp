{ 'targets': [
  { 'target_name' :   'hello_world'
  , 'sources'     : [ 'hello_world.cpp' ]
  , 'cflags_cc!'  : [ '-fno-rtti']
  , 'conditions'  : [ ['OS=="mac"', { 'xcode_settings': { 'GCC_ENABLE_CPP_RTTI': 'YES' }}]]
  , 'defines'     : [ 'N2O_MODULE_NAME=<(_target_name)']
  , 'include_dirs': ['../..']
  }
] }

