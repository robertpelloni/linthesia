# Linthesia - The Advanced Open-Source MIDI Visualizer

![Build Status](https://github.com/linthesia/linthesia/actions/workflows/c-cpp.yml/badge.svg)

Linthesia is a sophisticated, open-source fork of the classic piano-learning game Synthesia (version 0.6.1a). It provides a "Piano Hero" style interface where users can play music using a MIDI keyboard (or a PC keyboard) by following notes that fall from the top of the screen towards a virtual piano interface.

The project has evolved significantly to act as a modern, extensible tool for Linux systems (with support architectures for macOS and Windows), offering robust learning features, precise scoring, and seamless visual feedback.

## Features
* **"Piano Hero" Gameplay**: Falling notes visualizer perfectly synchronized to MIDI events.
* **Scoring System**: Real-time accuracy metrics including Perfect (<50ms), Good (<100ms), and Miss timing windows, combined with streak combo indicators.
* **Sight Reading Mode (F7)**: Procedurally rendered standard Grand Staff notation for traditional sheet music learning.
* **Wait Mode / Learning Mode**: The game pauses until you hit the correct keys, featuring a customizable grace period for rolled chords and natural playing.
* **Interactive Song Library**: Lightning-fast, real-time text-based search for MIDI files and directories.
* **Loop Practice**: Isolate difficult sections using A-B repeating loops across the interactive progress bar.
* **Extensive Customization**: Configurable keyboard sizes (88 to 37 keys), lead-in/lead-out timers, scroll speeds, track colors, and metronome capabilities.
* **Monorepo Orchestration**: Bundled with Python tools (`workspace_indexer.py`, `search_api.py`, `build_all.py`) for massive monorepo FTS5 indexing, automated testing, and validation.

## Installation & Setup

### Dependencies (Linux)
To compile Linthesia natively, ensure you have the required toolchains and libraries installed:
```bash
sudo apt-get update
sudo apt-get install -y build-essential meson ninja-build libtool-bin
sudo apt-get install -y libasound2-dev libsqlite3-dev libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libglibmm-2.4-dev libgtkmm-3.0-dev gettext libgtest-dev clang-format clang-tidy python3
```

### Build Instructions
Linthesia uses the modern `Meson` build system. We've included a `Makefile` wrapper for convenience.

```bash
# Clone the repository and update submodules
git clone https://github.com/linthesia/linthesia.git
cd linthesia
git submodule update --init --recursive

# Initialize the build directory and compile
make build

# Run the test suite (Google Test)
make test

# Install to system (requires root)
sudo ninja -C build install
```

## Running the Game

### Basic Usage
1. Execute `./build/src/linthesia` from your terminal.
2. Select a MIDI file (`.mid`) from the Song Library.
3. Configure your **Output Device** (your synthesizer) and **Input Device** (your MIDI keyboard) in the main menu.
4. Play!

### Audio Configuration (MIDI Routing)
Linthesia itself does not synthesize audio; it routes MIDI events to a system synthesizer. You must have a software synthesizer running.
*   **Fluidsynth**: `fluidsynth -a alsa -m alsa_seq /usr/share/sounds/sf2/FluidR3_GM.sf2`
*   **Timidity++**: `timidity -iA`

Once running, the synthesizer will appear in Linthesia's "Output Device" list.

### Keyboard Controls During Playback
*   **Space / Esc**: Pause or Resume the game.
*   **F1 / F2**: Set Loop A (Start point) and Loop B (End point).
*   **F3**: Clear Loop.
*   **F4 / F5**: Slow down or Speed up playback globally.
*   **F6**: Toggle Rhythm Practice mode (ignore pitch, focus strictly on timing).
*   **F7**: Toggle Sight Reading mode (Standard Grand Staff notation).
*   **Page Up / Down**: Jump backward or forward 5 seconds.
*   **< / >**: Shift octave up/down.

## Contribution Guidelines
We welcome contributions! Please review the following documentation before submitting pull requests:
*   [AGENTS.md](AGENTS.md): Master instructions and workflows for AI agents and human contributors.
*   [VISION.md](VISION.md) & [ROADMAP.md](ROADMAP.md): Our long-term goals and immediate feature requests.
*   [IDEAS.md](IDEAS.md): A collection of ambitious architectural overhauls (e.g., WebAssembly ports, AI co-pilots).

### Developer Tools
*   `make format`: Run `clang-format` on the codebase to adhere to Google C++ standards.
*   `make lint`: Run `clang-tidy` to catch potential warnings and static analysis issues.
*   `./scripts/workspace_indexer.py`: Build a SQLite FTS5 database to search the massive codebase quickly.
*   `./build_all.py`: Verify that all nested C++, Python, and Node projects compile successfully before committing.

## License
Linthesia is open-source software. See the `COPYING` file for detailed licensing information.
