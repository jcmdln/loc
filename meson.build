# meson.build

project(
  'loc', 'c',
  version: '0.1.0',
  default_options: [
    'c_std=c11',
    'optimization=g',
    'warning_level=3',
    'werror=true',
  ]
)

cc = meson.get_compiler('c')

c_args = '''
  -fPIC
  -fPIE
'''.split()

foreach arg : c_args
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
