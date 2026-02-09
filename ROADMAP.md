# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.1.0-dev)
Linthesia is a fully functional MIDI visualizer and learning tool for Linux.

### Major Milestone: v1.0.0
*   **Search**: Fully functional Song Library Search with text input support.
*   **Wait Mode Tolerance**: Improved "Learning" mode handles non-quantized/rolled chords gracefully (50ms window).
*   **Loop Practice**: Robust A-B repeat.
*   **Scoring**: Precision-based scoring with visual feedback.
*   **Architecture**: `MidiDriver` interface established for future portability.

### In Progress: v1.1.0
*   **Cross-Platform Port**: `AlsaMidiDriver` implementation created (refactoring in progress).
*   **Advanced Scoring**: Streaks and S-Rank added.

## Future Horizons

### Post-v1.1 Goals
*   **Refactor MidiComm**: Switch to using `MidiDriver` backend.
*   **Windows/macOS Support**: Implement `WinMidiDriver` and `CoreMidiDriver`.
*   **Built-in Synthesizer**: Remove the dependency on external synths by embedding FluidSynth.
*   **MIDI Recording**: Allow users to record their sessions.
*   **Sheet Music**: Render standard notation.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
