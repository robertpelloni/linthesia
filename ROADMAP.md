# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.0.0)
Linthesia is a fully functional, feature-complete MIDI visualizer and learning tool for Linux.

### Major Milestone: v1.0.0
*   **Search**: Fully functional Song Library Search with text input support.
*   **Wait Mode Tolerance**: Improved "Learning" mode handles non-quantized/rolled chords gracefully (50ms window).
*   **Loop Practice**: Robust A-B repeat.
*   **Scoring**: Precision-based scoring with visual feedback.
*   **Architecture**: `MidiDriver` interface established for future portability.

## Future Horizons

### Post-v1.0 Goals
*   **Cross-Platform Port**: Use the `MidiDriver` interface to implement Windows (WinMM) and macOS (CoreMIDI) backends.
*   **Built-in Synthesizer**: Remove the dependency on external synths by embedding FluidSynth.
*   **MIDI Recording**: Allow users to record their sessions.
*   **Sheet Music**: Render standard notation.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
