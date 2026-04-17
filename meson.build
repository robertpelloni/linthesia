project('linthesia', 'cpp',
  version : run_command('cat', 'VERSION', check: true).stdout().strip(),
  meson_version: '>=0.57.0',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

project_name = meson.project_name()
prefix = get_option('prefix')
datadir = get_option('datadir')

common_flags = []

musicdir = datadir / project_name / 'music'
if get_option('musicdir') != ''
  musicdir = get_option('musicdir')
endif
common_flags += [
  '-DMUSICDIR="@0@"'.format(prefix / musicdir)
]

install_subdir('music', install_dir: datadir / project_name )

graphdir = datadir / project_name / 'graphics'
if get_option('graphdir') != ''
  graphdir = get_option('graphdir')
endif
common_flags += [
  '-DGRAPHDIR="@0@"'.format(prefix / graphdir)
]

add_project_arguments(common_flags, language: 'cpp')

i18n = import('i18n')
gettext = project_name

source_root = meson.current_source_dir()
po_dir = source_root / 'po'

subdir('extra')
subdir('graphics')
subdir('po')
subdir('src')

import('gnome').post_install(
  glib_compile_schemas: true,
  gtk_update_icon_cache: true,
)


# Testing with Google Test
gtest_dep = dependency('gtest', main : true, required : false)
if gtest_dep.found()
  test_src = files('tests/audio_test.cpp')
  inc = include_directories('src', 'src/libmidi')
  # We need to compile the test executable linking with libmidi and other components
  # For now, just a placeholder test to verify integration
  linthesia_test = executable('linthesia-test', test_src, include_directories: inc, dependencies: [gtest_dep])
  test('Basic Audio Tests', linthesia_test)
else
  message('Google Test not found, skipping tests.')
endif
