# Linthesia Architectural Overview

## Module Breakdown

Linthesia is organized into several key modules to ensure clear separation of concerns, maintainability, and future cross-platform portability.

### 1. `libmidi` (Core MIDI Parsing)
*   **Location**: `src/libmidi/`
*   **Responsibility**: Parsing standard MIDI files (`.mid`, `.midi`), managing tracks, events, and timings. It is designed to be entirely agnostic of rendering or audio output backends.
*   **Key Classes**: `Midi`, `MidiTrack`, `MidiEvent`.

### 2. `GameState` (Game Logic & Flow)
*   **Location**: `src/` (e.g., `PlayingState.cpp`, `SongLibState.cpp`, `TitleState.cpp`)
*   **Responsibility**: Managing the various screens and interactions of the application. It handles user input (keyboard, mouse, MIDI keyboard) and transitions between states (using `GameStateManager`).
*   **Key Classes**: `GameStateManager`, `PlayingState`, `SongLibState`.

### 3. Graphics & Rendering
*   **Location**: `src/Renderer.cpp`, `src/KeyboardDisplay.cpp`, `src/SheetMusicDisplay.cpp`
*   **Responsibility**: Translating game state and MIDI data into visual feedback. Currently undergoing a massive transition from raw SDL2/OpenGL to native GTKmm/Pango contexts for modern text rendering and UI integration.
*   **Dependencies**: `OpenGL`, `SDL2` (windowing/input), `GTKmm 3.0` (UI/Text).

### 4. Audio Output (MIDI Drivers)
*   **Location**: `src/MidiComm.cpp`, `src/drivers/`
*   **Responsibility**: Routing parsed MIDI events to hardware synthesizers or software sequencers.
*   **Current Backend**: ALSA (Linux specific).
*   **Future Backend**: `FluidSynthMidiDriver` (Mocked; awaiting proper `libfluidsynth-dev` integration for cross-platform built-in synthesis).

### 5. Utilities & Storage
*   **Location**: `src/UserSettings.cpp`, `src/ScoreDB.cpp` (implicit in `main`)
*   **Responsibility**: Persistent storage of user preferences (via GSettings/Gio) and gameplay high scores (via SQLite3).

## Build System
*   **Tool**: Meson + Ninja
*   **Configuration**: `meson.build` at the root handles global variables, localization, and links subdirectories. `src/meson.build` defines the main executable dependencies and links the `libmidi` static library.

## Documentation Generation
*   **Tool**: Doxygen
*   **Output**: HTML documentation is automatically generated in `docs/api/html` when the `ninja doc` target is executed, parsed from the `src/` directory headers.
