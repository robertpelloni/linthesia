# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v0.10.3)
Linthesia is a fully functional MIDI visualizer and learning tool for Linux. It supports playing MIDI files, configuring tracks, and extensive customization. The codebase is actively transitioning to GTKmm/Pango for text rendering.

### Recently Completed
*   **v0.10.3 Features**:
    *   **Doxygen API Integration**: `ninja doc` target auto-generates C++ HTML documentation into `docs/api`.
*   **v0.10.2 Features**:
    *   **Intelligent Agent Search**: `workspace_indexer.py` (SQLite FTS5) and `search_api.py` (FastMCP) allow agents to rapidly index and query across the monorepo codebase. Supports exact match, prefix match, and Regex pattern execution.
*   **v0.9.1 Features**:
    *   **Song Library Search**: Type to filter song tiles in real-time.
*   **v0.9.0 Features**:
    *   **Loop Practice**: A-B repeat functionality with F1/F2 keys.
    *   **Pause Menu**: Interactive buttons for Resume/Quit.

## Upcoming Features

### Short Term (v1.0.0)
*   **[x] Scoring System**: Implement a scoring algorithm (Perfect, Good, Miss) and Streak popup UI representation.
*   **[x] Wait Mode Polish**: Improve the "Learning" mode grace period logic to handle rolled chords cleanly.
*   **[x] Sight Reading**: Implement `SheetMusicDisplay` for standard grand staff notation (Treble/Bass clef).
*   **[ ] Complete GTKmm Rendering**: Eliminate legacy dummy context structs (`GLContext()`, `PGContext()`) in `main.cpp` and implement true native GTK windowing.

### Medium Term
*   **[ ] Built-in Synthesizer**: Integrate FluidSynth for out-of-the-box audio without ALSA dependencies (blocked currently by missing `libfluidsynth-dev`).
*   **[ ] Cross-Platform Audio**: WinMM (Windows) and CoreAudio (macOS) wrappers natively within `src/drivers/`.

## Submodule Analysis: `pianogame`
The `pianogame` submodule is the reference implementation (Synthesia 0.6.1a).
*   **Status**: Frozen reference.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.

## Future Innovations & Pivots
See `IDEAS.md` for a comprehensive list of ambitious concepts including WebAssembly ports, AI Hand Tracking, Multiplayer Battles, and Procedural Sheet Music engines.
