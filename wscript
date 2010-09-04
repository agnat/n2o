import sys
import Options
from os import unlink, link
from os.path import exists 

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

def build(bld):
  lib = bld.new_task_gen('cxx', 'cstaticlib')
  lib.target = 'n2o'
  lib.source = 'src/function_wrapper.cpp'
  lib.export_incdirs = 'src'
  lib.includes = '/Volumes/Stuff/Users/david/node/include/node /opt/local/include'

  ex = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  ex.target = 'binding'
  ex.source = 'example/binding.cpp'
  ex.uselib_local = 'n2o'
  ex.includes = 'src /opt/local/include'
                
def shutdown():
  if exists('binding.node'): unlink('binding.node')
  if Options.commands['build']:
    link('build/default/binding.node', 'binding.node')


# vim: filetype=python :
