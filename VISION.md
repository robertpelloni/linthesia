# Vision for Linthesia

## The Ultimate Open-Source Piano Learning Software

Linthesia aims to be the definitive, feature-complete, open-source alternative to proprietary software like Synthesia and Melodics on the Linux platform (and eventually cross-platform). It is not just a "clone"; it is an enhancement, offering robust features for serious practice and gamified learning.

## Core Philosophy
1.  **Completeness**: If a feature exists in the backend (e.g., MIDI input), it must be fully exposed in the frontend (Settings menu, visual indicators).
2.  **Accessibility**: Easy to set up, easy to configure. No hidden config files.
3.  **Visual Feedback**: Every action (hit, miss, wait) has a visual response. The interface should "feel" alive.
4.  **Education First**: Features like "Wait Mode", "Looping", "Sheet Music", and "Note Labels" are prioritized to aid learning.

## Key Features (Target)
*   **Gameplay**:
    *   Falling Notes (Classic).
    *   Sheet Music (Standard Notation).
    *   Wait Mode (Pauses until you hit the right note).
    *   Rhythm Mode (Timing practice).
*   **Library**:
    *   Robust search and filtering.
    *   History and Statistics (Grades, Streaks).
*   **Hardware**:
    *   Low-latency MIDI (ALSA/Jack/FluidSynth).
    *   Lighted Keys support (output MIDI).

## Design
*   **UI**: Clean, large buttons (touch-friendly where possible), consistent color scheme (Tango-based).
*   **Architecture**: Modular `GameState` system. `MidiDriver` abstraction for cross-platform support.

## Future Goals
*   **Built-in Synth**: FluidSynth integration to remove dependency on external synths (QSynth/Timidity).
*   **Cross-Platform**: Windows (WinMM) and macOS (CoreMIDI) drivers.
*   **Network**: Leaderboards or multiplayer? (Long term).
