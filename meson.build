# meson.build

project(
  'loc', 'c',
  version: '0.1.0')

cc = meson.get_compiler('c')

if get_option('buildtype').startswith('debug')
  c_args = '''
    -Og
    -Wall
    -Werror
    -Wextra
    -Wpedantic
  '''.split()
endif

if get_option('buildtype').startswith('release')
c_args = '''
  -O2
'''.split()
endif

extra_args = '''
  -std=c89
  -fPIC
  -fPIE
'''.split()

foreach arg : c_args
  if cc.has_argument(arg)
    add_project_arguments(arg, language: 'c')
  endif
endforeach

foreach arg : extra_args
  if cc.has_argument(arg)
    add_project_arguments(arg, language: 'c')
  endif
endforeach

add_project_arguments('-D_DEFAULT_SOURCE', language: 'c')

subdir('src')
includes = include_directories('src')

executable(
  'loc', loc_sources,
  include_directories: includes,
  install: false
)
