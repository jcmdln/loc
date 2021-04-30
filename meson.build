# meson.build

project(
  'loc',
  'c',
  default_options: [
    'b_colorout=auto',
    'b_lto=false',
    'b_lto_threads=0',
    'b_pie=false',
    'b_sanitize=address,undefined',
    'buildtype=debug',
    'c_std=c17',
    'debug=true',
    'optimization=0',
    'strip=false',
    'warning_level=3',
    'werror=true',
  ],
  license: 'ISC',
  meson_version: '>=0.53.0',
  version: '0.1.0',
)

#
# Compilation
#

cc = meson.get_compiler('c', native: true)

if cc.has_argument('-fno-omit-frame-pointer')
  add_project_arguments('-fno-omit-frame-pointer', language: 'c')
endif

if host_machine.system().startswith('freebsd')
  if cc.has_argument('-D_C11_SOURCE')
    add_project_arguments('-D_C11_SOURCE', language: 'c')
  endif
elif host_machine.system().startswith('linux')
  if cc.has_argument('-D_DEFAULT_SOURCE')
    add_project_arguments('-D_DEFAULT_SOURCE', language: 'c')
  else
    add_project_arguments('-D_BSD_SOURCE', language: 'c')
  endif
elif host_machine.system().startswith('openbsd')
  if cc.has_argument('')
    add_project_arguments('', language: 'c')
  endif
endif

#
# Executables
#

loc_sources = [
  'src/loc.c',
  'src/loc.h',
]

executable(
  'loc',
  loc_sources,
  install: false,
)
