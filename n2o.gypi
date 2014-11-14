{ 'target_defaults':
  { 'include_dirs'     : [ '.' ]
  , 'defines'          : [ 'N2O_MODULE_NAME=>(_target_name)']
  , 'cflags!'          : [ '-fno-rtti', '-fno-exceptions' ]
  , 'target_conditions': [['OS=="mac"',
    { 'xcode_settings':
        { 'GCC_ENABLE_CPP_RTTI'      : 'YES'
        , 'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
        }
    }]]
  }
}
