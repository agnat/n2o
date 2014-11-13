{ 'targets': [
  { 'target_name' :   'n2o'
  , 'sources'     : [ 'src/function_wrapper.cpp'
                    , 'src/registry.cpp'
                    , 'src/builtin_converters.cpp'
                    , 'src/from_js.cpp'
                    , 'src/binding.cpp'
                    ]
  , 'include_dirs': [ '.']
  , 'cflags_cc!'  : [ '-fno-rtti']
  , 'conditions'  : [ ['OS=="mac"', { 'xcode_settings': { 'GCC_ENABLE_CPP_RTTI': 'YES' }}]]
  }
] }

