# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia.

## Current Status (v0.9.0)
Linthesia is a fully functional MIDI visualizer and learning tool for Linux. It supports playing MIDI files, configuring tracks, and extensive customization.

### Recently Completed
*   **v0.9.0 Features**:
    *   **Loop Practice**: A-B repeat functionality with F1/F2 keys.
    *   **Pause Menu**: Interactive buttons for Resume/Quit.
    *   **Keyboard Size**: Verified logic for 37-88 key support.
    *   **Agent Documentation**: Unified instructions for AI contributors.
    *   **Song Search**: Added basic search filter logic (UI ready, input needs wiring).
    *   **MIDI Abstraction**: Created `MidiDriver` interface for future cross-platform support.
*   **v0.8.0 Features**:
    *   **Settings Menu**: Configurable Lead-In, Lead-Out, Scroll Speed, Metronome.
    *   **Metronome**: Audio and Visual feedback.
    *   **Documentation**: Comprehensive User Manual.

## Upcoming Features

### Short Term (v1.0.0)
*   **[ ] Text Input**: Hook up SDL text input events to `SongLibState` to enable the search bar.
*   **[ ] Scoring Polish**: Refine scoring thresholds and visual feedback.
*   **[ ] Wait Mode Tolerance**: Implement a "grace window" for sloppy MIDI files where chords aren't perfectly quantized.

### Medium Term
*   **[ ] Built-in Synthesizer**: Integrate FluidSynth.
*   **[ ] Cross-Platform Support**: Implement `WinMidiDriver` and `CoreMidiDriver` using the new abstraction.
*   **[ ] MIDI Recording**: User performance recording.

## Submodule Analysis: `pianogame`
The `pianogame` submodule is the reference implementation (Synthesia 0.6.1a).
*   **Status**: Frozen reference.
*   **Gap Analysis**: Most core features are now ported or reimplemented in Linthesia.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute.
