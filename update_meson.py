import sys

with open('src/meson.build', 'r') as f:
    content = f.read()

# Fix the dependency initialization order
content = content.replace("""
# Platform specific dependencies
if host_machine.system() == 'windows'
  dependencies += meson.get_compiler('cpp').find_library('winmm')
elif host_machine.system() == 'darwin'
  dependencies += dependency('appleframeworks', modules : ['CoreFoundation', 'CoreMIDI'])
endif

dependencies = [
  dependency('alsa'),
  dependency('gl'),
  dependency('giomm-2.4'),
  dependency('gtkmm-3.0'),
  dependency('sqlite3'),
  dependency('SDL2'),

  dependency('SDL2_image'),
  dependency('threads')
]
""", """
dependencies = [
  dependency('alsa'),
  dependency('gl'),
  dependency('giomm-2.4'),
  dependency('gtkmm-3.0'),
  dependency('sqlite3'),
  dependency('SDL2'),
  dependency('SDL2_image'),
  dependency('threads')
]

# Platform specific dependencies
if host_machine.system() == 'windows'
  dependencies += meson.get_compiler('cpp').find_library('winmm')
elif host_machine.system() == 'darwin'
  dependencies += dependency('appleframeworks', modules : ['CoreFoundation', 'CoreMIDI'])
endif
""")

with open('src/meson.build', 'w') as f:
    f.write(content)
