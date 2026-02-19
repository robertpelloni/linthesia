# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.3.0)
Linthesia is a fully functional, feature-complete MIDI visualizer and learning tool for Linux.

### Major Milestone: v1.3.0
*   **Sheet Music**: Basic staff rendering integrated into the game. Toggle with F7.
*   **Scoring Polish**: Early/Late indicators for timing feedback.
*   **MidiDriver**: Full abstraction layer.

### Previous Milestones
*   **v1.2.0**: Rhythm Mode, Judgement Line.
*   **v1.1.0**: Score Persistence, Search, Settings.

## Future Horizons

### Post-v1.3 Goals
*   **Cross-Platform Port**: Use the `MidiDriver` interface to implement Windows (WinMM) and macOS (CoreMIDI) backends.
*   **Built-in Synthesizer**: Remove the dependency on external synths by embedding FluidSynth.
*   **MIDI Recording**: Allow users to record their sessions.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
