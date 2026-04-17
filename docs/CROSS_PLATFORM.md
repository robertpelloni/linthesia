# Cross-Platform Support for Linthesia

While Linthesia is primarily developed and tested on Linux systems, the architecture (relying on Meson, SDL2, and generic APIs like `MidiDriver`) is designed to support cross-platform compilation.

## Windows

### Prerequisites
To build Linthesia on Windows, you will need the MSYS2 environment, which provides a package management system (Pacman) and a Unix-like shell.

1. Install [MSYS2](https://www.msys2.org/).
2. Open the MSYS2 MinGW 64-bit terminal.
3. Install the required toolchain and dependencies:
   ```bash
   pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-meson mingw-w64-x86_64-ninja
   pacman -S mingw-w64-x86_64-sdl2 mingw-w64-x86_64-sdl2_image mingw-w64-x86_64-sdl2_ttf
   pacman -S mingw-w64-x86_64-sqlite3 mingw-w64-x86_64-gtkmm3 mingw-w64-x86_64-glib2
   ```

### MIDI Backend
Windows uses the Win32 Multimedia API (`mmeapi.h` / `midiOutShortMsg`).
A new `WindowsMidiDriver` class implementing the `MidiDriver` interface must be compiled instead of the Linux `AlsaMidiDriver`.

### Building
```bash
meson setup build
ninja -C build
```

## macOS

### Prerequisites
Use [Homebrew](https://brew.sh/) to install dependencies.

1. Install Xcode Command Line Tools: `xcode-select --install`
2. Install dependencies:
   ```bash
   brew install meson ninja sdl2 sdl2_image sdl2_ttf sqlite glib gtkmm3
   ```

### MIDI Backend
macOS uses the CoreMIDI framework.
A new `CoreMidiDriver` class implementing the `MidiDriver` interface must be created. You must link against `-framework CoreMIDI -framework CoreAudio` in `meson.build`.

### Building
```bash
meson setup build
ninja -C build
```
