{ 'includes': ['n2o.gypi' ]
, 'targets': [
  { 'target_name' :   'n2o'
  , 'sources'     : [ 'src/function_wrapper.cpp'
                    , 'src/registry.cpp'
                    , 'src/builtin_converters.cpp'
                    , 'src/from_js.cpp'
                    , 'src/type_id.cpp'
                    , 'src/binding.cpp'
                    ]
  , 'include_dirs': [ '.']
  }
] }

