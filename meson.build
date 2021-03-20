# meson.build

project(
  'loc',
  'c',
  default_options: ['c_std=c18'],
  license: 'ISC',
  meson_version: '>=0.53.0',
  version: '0.1.0',
)

if get_option('buildtype').startswith('debug')
  build_options = [
    'optimization=g',
    'strip=false',
    'warning_level=3',
    'werror=true',
    'b_lto=false',
    'b_pie=false',
    'b_sanitize=undefined',
  ]
endif

if get_option('buildtype').startswith('release')
  build_options = [
    'optimization=3',
    'strip=true',
    'warning_level=0',
    'werror=false',
    'b_lto=true',
    'b_pie=true',
    'b_sanitize=none',
  ]
endif

cc = meson.get_compiler('c')
add_project_arguments('-D_DEFAULT_SOURCE', language: 'c')

loc_sources = [
  'src/loc.h',
  'src/main.c',
  'src/langs.c',
  'src/parse.c',
  'src/results.c',
]

executable(
  'loc',
  loc_sources,
  install: false,
  override_options: build_options,
)
