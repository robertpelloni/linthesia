# Submodule Architecture and Project Structure

Linthesia utilizes Git submodules to maintain strict version control over critical upstream dependencies, primarily the original Synthesia codebase which serves as our architectural reference.

## Project Directory Structure

```
linthesia/
├── build/               # Generated object files, Ninja build scripts, and compiled binaries. Do not edit.
├── docs/                # Project documentation, including architectural overviews and Doxygen API HTML.
├── extra/               # Gio settings schemas (.gschema.xml) for persistent user preferences.
├── graphics/            # Image assets (.png, .tga) loaded dynamically at runtime.
├── music/               # Default MIDI files bundled with the installation.
├── pianogame/           # [SUBMODULE] The original Synthesia 0.6.1a codebase.
├── po/                  # Localization files (.pot, .po) for multi-language support.
├── scripts/             # Python orchestration tools (indexer, health checker, search API).
├── src/                 # The core C++ source code.
│   ├── drivers/         # Audio output drivers (ALSA, FluidSynth, etc).
│   └── libmidi/         # Platform-agnostic MIDI parsing library.
└── tests/               # Google Test (gtest) C++ unit tests.
```

## Submodules

### `pianogame`
*   **Path**: `/pianogame`
*   **Description**: The original open-source release of Synthesia (version 0.6.1a). This directory is treated as a frozen reference implementation. The logic within Linthesia heavily adapts and modernizes the algorithms found here, translating them from legacy SDL/Win32 APIs to modern C++14 and GTKmm structures.
*   **Version**: Synthesia 0.6.1a
*   **Status**: Frozen. Not actively compiled into the main Linthesia executable, but acts as the master reference document for rendering calculations (e.g. `KeyboardDisplay` and `TrackProperties`).
