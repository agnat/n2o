{ 'target_defaults':
  { 'include_dirs': [ '.' ]
  , 'cflags!'     : [ '-fno-rtti' ]
  , 'defines'     : [ 'N2O_MODULE_NAME=>(_target_name)']
  , 'target_conditions'  : [ ['OS=="mac"', { 'xcode_settings': { 'GCC_ENABLE_CPP_RTTI': 'YES' }}]]
  }
}
