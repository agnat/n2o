{ 'target_defaults': {'dependencies': ['../binding.gyp:n2o']}
, 'targets':
  [ {'target_name': 'functions',   'sources': ['0010_functions.cpp']}
  , {'target_name': 'classes',     'sources': ['0020_classes.cpp']}
  , {'target_name': 'exceptions',  'sources': ['0030_exceptions.cpp']}
  , {'target_name': 'init_except', 'sources': ['0030_init_except.cpp']}
  ]
}

