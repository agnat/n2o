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
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'hello_world'
  obj.source = bld.path.ant_glob('src/*.cpp')
                

def shutdown():
  # HACK to get binding.node out of build directory.
  # better way to do this?
  if exists('lib/hello_world.node'): unlink('lib/hello_world.node')
  if Options.commands['build']:
    link('build/default/hello_world.node', 'lib/hello_world.node')

# vim: set filetype=python :
