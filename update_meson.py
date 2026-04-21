import sys

with open('meson.build', 'r') as f:
    content = f.read()

# Replace the test definitions
old_tests = """  test_src = files('tests/audio_test.cpp')
  inc = include_directories('src', 'src/libmidi')
  # We need to compile the test executable linking with libmidi and other components
  # For now, just a placeholder test to verify integration
  linthesia_test = executable('linthesia-test', test_src, include_directories: inc, dependencies: [gtest_dep])
  test('Basic Audio Tests', linthesia_test)"""

new_tests = """  test_src = files('tests/audio_test.cpp', 'tests/test_libmidi.cpp')
  inc = include_directories('src', 'src/libmidi')
  # We need to compile the test executable linking with libmidi and other components
  # We can't access `libmidi` directly if it's defined in a subdir after this.
  # So we will move the test definition down.
"""

# Let's completely replace the Google Test block to be cleaner.
