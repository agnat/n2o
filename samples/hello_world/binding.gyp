{ "targets": [
  { "target_name" : "hello_world"
  , "sources"     : [ "hello_world.cpp" ]
  , "include_dirs": ["../.."]
  , "cflags_cc!"  : [ "-fno-rtti" ]
  , "conditions"  : [ ["OS=='mac'", { "xcode_settings": { "GCC_ENABLE_CPP_RTTI": "YES" } }]
]
  }
] }

