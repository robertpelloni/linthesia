# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.0.0)
Linthesia is a fully functional MIDI visualizer and learning tool for Linux. It supports playing MIDI files, configuring tracks, and extensive customization. The codebase is actively transitioning to GTKmm/Pango for text rendering.

### Recently Completed
*   **v0.9.1 Features**:
    *   **Song Library Search**: Type to filter song tiles in real-time.
    *   **Bug Fixes**: Resolved all compilation blockers caused by improper merge conflict resolution and syntax destruction.
*   **v0.9.0 Features**:
    *   **Loop Practice**: A-B repeat functionality with F1/F2 keys.
    *   **Pause Menu**: Interactive buttons for Resume/Quit.

## Upcoming Features

### GTKmm Migration (Phase 3)
*   **[x] Gtk::Window Swap**: Replace `SDL_Window` with `Gtk::Window` and `Gtk::GLArea`.
*   **[x] InputManager Abstraction**: Extract SDL input logic to prepare for GTKmm input signals.


### Short Term (v1.0.0)
*   **[x] Scoring System**: Implement a scoring algorithm (Perfect, Good, Miss) and Streak popup UI representation.
*   **[x] Wait Mode Polish**: Improve the "Learning" mode grace period logic to handle rolled chords cleanly.
*   **[x] Sight Reading**: Implement `SheetMusicDisplay` for standard grand staff notation (Treble/Bass clef).

### Medium Term
*   **[x] Built-in Synthesizer**: Integrate FluidSynth for out-of-the-box audio without ALSA dependencies.
*   **[x] Cross-Platform Support**: Windows/macOS build instructions and abstraction.

## Submodule Analysis: `pianogame`
The `pianogame` submodule is the reference implementation (Synthesia 0.6.1a).
*   **Status**: Frozen reference.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.


## Monorepo & Operations
*   **[x] Omniscient Orchestration (Phase 4)**: Implemented SQLite FTS5 Workspace Indexer (`workspace_indexer.py` (parallel processing)) and FastMCP Search API (`search_api.py`) for "needle-in-a-haystack" analysis.
*   **[x] Build Verification**: Global `build_all.py` scanner validates monorepo and submodules stability.
*   **[x] Live Health Monitoring**: Created `health_check.py` to probe the project environment and verify critical system dependencies in real-time.

## Future Innovations & Pivots
See `IDEAS.md` for a comprehensive list of ambitious concepts including WebAssembly ports, AI Hand Tracking, Multiplayer Battles, and Procedural Sheet Music engines.


## Jules Autopilot (Go Runtime)
* [x] **Git Diff Monitoring**: Background Shadow Pilot anomaly detection is implementing native git diff monitoring in Go.
* [x] **CI Pipeline Auto-Fix**: Shadow Pilot anomaly logging requires CI pipeline auto-fix logic.
* [x] **Submodule Status Check**: Wire real-time submodule git status checks in the Go backend to the `/system/status` UI.
