# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v1.2.0+)
Linthesia is a fully functional, feature-complete MIDI visualizer and learning tool for Linux.

### Recent Accomplishments
*   **v1.2.0**: Rhythm Mode, Judgement Line, MidiDriver Refactor.
*   **v1.1.0**: Score Persistence, Song Library Search, Settings Menu.
*   **Polish**: Configurable "Wait Tolerance" for chord practice, improved search UI.

## Upcoming Features

### Short Term
*   **[ ] Scoring Polish**: Add "Early/Late" indicators to scoring popups.
*   **[ ] Sheet Music (Phase 1)**: Basic staff rendering for single melody lines.
*   **[ ] MIDI Output**: Ensure PC keyboard input routes to MIDI output (Audio Test implemented, but gameplay integration needs verification).

### Medium Term
*   **[ ] Built-in Synthesizer**: Integrate FluidSynth.
*   **[ ] Cross-Platform Support**: Implement `WinMidiDriver` and `CoreMidiDriver`.
*   **[ ] MIDI Recording**: User performance recording.

## Technical Debt & Polish
*   **Cleanup**: Remove legacy TODO comments in `SongLibState` and `MidiComm`.
*   **Refactor**: Fully transition `MidiComm` to use `MidiDriver` for all operations (mostly done).

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
