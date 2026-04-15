# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v0.9.1)
Linthesia is a fully functional MIDI visualizer and learning tool for Linux. It supports playing MIDI files, configuring tracks, and extensive customization. The codebase is actively transitioning to GTKmm/Pango for text rendering.

### Recently Completed
*   **v0.9.1 Features**:
    *   **Song Library Search**: Type to filter song tiles in real-time.
    *   **Bug Fixes**: Resolved all compilation blockers caused by improper merge conflict resolution and syntax destruction.
*   **v0.9.0 Features**:
    *   **Loop Practice**: A-B repeat functionality with F1/F2 keys.
    *   **Pause Menu**: Interactive buttons for Resume/Quit.

## Upcoming Features

### Short Term (v1.0.0)
*   **[ ] Scoring System**: Implement a scoring algorithm (Perfect, Good, Miss) and Streak popup UI representation.
*   **[x] Wait Mode Polish**: Improve the "Learning" mode grace period logic to handle rolled chords cleanly.
*   **[x] Sight Reading**: Implement `SheetMusicDisplay` for standard grand staff notation (Treble/Bass clef).

### Medium Term
*   **[ ] Built-in Synthesizer**: Integrate FluidSynth for out-of-the-box audio without ALSA dependencies.
*   **[ ] Cross-Platform Support**: Windows/macOS build instructions and abstraction.

## Submodule Analysis: `pianogame`
The `pianogame` submodule is the reference implementation (Synthesia 0.6.1a).
*   **Status**: Frozen reference.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
