{ 'targets': [
  { 'target_name' :   'n2o'
  , 'type'        :   'static_library'
  , 'sources'     : [ '../../src/function_wrapper.cpp'
                    , '../../src/registry.cpp'
                    , '../../src/builtin_converters.cpp'
                    , '../../src/from_js.cpp'
                    ]
  , 'include_dirs': [ '../..']
  , 'cflags_cc!'  : [ '-fno-rtti']
  , 'conditions'  : [ ['OS=="mac"', { 'xcode_settings': { 'GCC_ENABLE_CPP_RTTI': 'YES' }}]]
  , 'direct_dependent_settings': { 'include_dirs': ['../..']}
  }
, { 'target_name' :   'hello_world'
  , 'sources'     : [ 'hello_world.cpp'
                    ]
  , 'dependencies': [ 'n2o' ]
  , 'cflags_cc!'  : [ '-fno-rtti']
  , 'conditions'  : [ ['OS=="mac"', { 'xcode_settings': { 'GCC_ENABLE_CPP_RTTI': 'YES' }}]]
  , 'defines'     : [ 'N2O_MODULE_NAME=<(_target_name)']
  }
] }

