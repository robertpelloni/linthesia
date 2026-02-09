# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.1.0)
Linthesia is a fully functional, feature-complete MIDI visualizer and learning tool for Linux.

### Major Milestone: v1.1.0
*   **Scoring & Persistence**: Added local database (SQLite) to save scores, grades, and streaks. Best scores are displayed in the song library.
*   **Assessment**: Tracks "Perfect" vs "Good" hits and assigns grades (S, A, B...) and streaks.
*   **Search**: Fully functional Song Library Search with text input support.
*   **Wait Mode Tolerance**: Improved "Learning" mode handles non-quantized/rolled chords gracefully.
*   **Loop Practice**: Robust A-B repeat.
*   **Architecture**: `MidiDriver` interface and `AlsaMidiDriver` implementation.

## Future Horizons

### Post-v1.1 Goals
*   **Cross-Platform Port**: Use the `MidiDriver` interface to implement Windows (WinMM) and macOS (CoreMIDI) backends.
*   **Built-in Synthesizer**: Remove the dependency on external synths by embedding FluidSynth.
*   **MIDI Recording**: Allow users to record their sessions.
*   **Sheet Music**: Render standard notation.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
