import sys

with open('src/meson.build', 'r') as f:
    content = f.read()

# Add fluidsynth dependency and the compilation flag
new_deps = """dependencies = [
  dependency('alsa'),
  dependency('gl'),
  dependency('giomm-2.4'),
  dependency('gtkmm-3.0'),
  dependency('sqlite3'),
  dependency('SDL2'),
  dependency('SDL2_ttf'),
  dependency('SDL2_image'),
  dependency('threads'),
  dependency('fluidsynth', required: false)
]"""

content = content.replace("dependencies = [", new_deps + "\n#")
content = content.replace("dependency('threads')\n]", "")

# Add FluidSynthMidiDriver to sources
sources_target = "'FileSelector.cpp',"
sources_new = "'FileSelector.cpp',\n           'drivers/FluidSynthMidiDriver.cpp',"
content = content.replace(sources_target, sources_new)

# Add compiler arg for USE_FLUIDSYNTH
exec_target = "executable('linthesia',"
exec_new = "executable('linthesia',\n           cpp_args: ['-DUSE_FLUIDSYNTH'],"
content = content.replace(exec_target, exec_new)

with open('src/meson.build', 'w') as f:
    f.write(content)
