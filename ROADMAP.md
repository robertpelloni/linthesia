# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.3.0-dev)
Linthesia is a fully functional, feature-complete MIDI visualizer and learning tool for Linux.

### In Progress: v1.3.0
*   **Sheet Music**: Basic staff rendering implemented (`SheetMusicDisplay`). Needs integration into `PlayingState`.
*   **FluidSynth**: Blocked by missing dev libs in current environment, deferred.

### Major Milestone: v1.2.0
*   **MIDI Driver Integration**: Full refactor of `MidiComm` to use the `MidiDriver` interface.
*   **Rhythm Mode**: New game mode.
*   **Visual Polish**: Added "Judgement Line".

## Future Horizons

### Post-v1.3 Goals
*   **Sheet Music Integration**: Toggle view in `PlayingState`.
*   **Cross-Platform Port**: Use the `MidiDriver` interface to implement Windows (WinMM) and macOS (CoreMIDI) backends.
*   **Built-in Synthesizer**: Remove the dependency on external synths by embedding FluidSynth.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
