import sys
import Options
from os import unlink, link
from os.path import exists 

waf_overlay = './tools/wafadmin/3rdparty'

def set_options(opt):
  opt.tool_options('compiler_cxx')
  opt.tool_options('boost', tooldir=waf_overlay)

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  conf.check_tool('boost', tooldir=waf_overlay)

  conf.check_boost()

def build(bld):
  lib = bld.new_task_gen('cxx', 'cstaticlib')
  lib.target = 'n2o'
  lib.source = 'src/function_wrapper.cpp'
  lib.export_incdirs = 'src'
  lib.includes = bld.env.CPPPATH_NODE
  lib.uselib = 'BOOST'

  ex = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  ex.target = 'binding'
  ex.source = 'example/binding.cpp'
  ex.uselib_local = 'n2o'
  ex.includes = 'src'
                
def shutdown():
  if exists('binding.node'): unlink('binding.node')
  if Options.commands['build']:
    link('build/default/binding.node', 'binding.node')


# vim: filetype=python :
