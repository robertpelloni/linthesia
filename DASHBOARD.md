# Dashboard

This dashboard provides an overview of the Linthesia project structure, dependencies, and build components.

## Submodules

| Submodule | Path | Version/Commit | Purpose | Status |
| :--- | :--- | :--- | :--- | :--- |
| `pianogame` | `pianogame/` | `05077cf` (approx) | Original source (Synthesia 0.6.1a) | Frozen/Reference |

## Dependencies

| Dependency | Version | Purpose |
| :--- | :--- | :--- |
| `sdl2` | `2.x` | Graphics, Window Management, Input |
| `sdl2_image` | `2.x` | Loading PNG/TGA textures |
| `sdl2_ttf` | `2.x` | Rendering TrueType fonts |
| `alsa-lib` | `1.x` | MIDI communication (Linux) |
| `sqlite3` | `3.x` | User database (scores, history) |
| `gtkmm-3.0` | `3.x` | Used for `glib-compile-schemas` (Settings) |
| `meson` | `>=0.57.0` | Build system |

## Project Structure

### Root Directory
*   `VERSION`: Single source of truth for the project version.
*   `meson.build`: Main build configuration.
*   `README.md`: User manual and installation guide.
*   `AGENTS.md`: Instructions for AI contributors.
*   `VISION.md`: Long-term project goals.
*   `CHANGELOG.md`: Detailed history of changes.

### Source Code (`src/`)
*   `main.cpp`: Entry point. Initializes SDL, ALSA, and the Game State Manager.
*   `GameState.cpp` / `.h`: Base class for game screens (Title, Playing, Settings, etc.).
*   `TitleState.cpp`: Main menu logic.
*   `PlayingState.cpp`: Core gameplay loop (notes falling, scoring).
*   `SettingsState.cpp`: Configuration menu logic.
*   `MidiComm.cpp` / `.h`: MIDI input/output handling via ALSA sequencer.
*   `Renderer.cpp`: OpenGL/SDL rendering wrapper.
*   `UserSettings.cpp`: GSettings wrapper for saving preferences.

### Libraries (`src/libmidi/`)
*   `Midi.cpp`: Parsing logic for Standard MIDI Files (.mid).
*   `MidiEvent.cpp`: Handling individual MIDI messages (Note On/Off).
*   `Note.h`: Data structures for musical notes.

### Resources (`graphics/`)
*   `*.tga`: User interface textures (buttons, keys).
*   `*.png`: Application icon.
*   `*.ttf`: Font files (FreeSans, FreeSerif).

### Extras (`extra/`)
*   `*.desktop`: Desktop entry for application menus.
*   `*.gschema.xml`: Schema definition for GSettings (user preferences).
*   `*.metainfo.xml`: AppStream metadata for software centers.

## Build Status
![Build Status](https://github.com/linthesia/linthesia/actions/workflows/c-cpp.yml/badge.svg)

## Documentation Status
*   **User Manual**: Complete (`README.md`).
*   **Developer Guide**: Complete (`AGENTS.md`).
*   **Roadmap**: In Progress (`ROADMAP.md`).
