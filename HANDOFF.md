# Handoff Notes

## Current State
*   **Version**: 1.2.1
*   **Branch**: `feature-search-and-polish` (merged)
*   **Key Achievements**:
    *   **Search**: Functional with UI and Text Input.
    *   **Architecture**: `MidiDriver` interface + `AlsaMidiDriver`.
    *   **Polish**: Wait Mode Tolerance, Rhythm Mode, Score Persistence.

## Critical Next Steps
1.  **Sheet Music**: Implement `SheetMusicDisplay`. This is the "White Whale".
2.  **Cross-Platform**: Implement `WinMidiDriver` using the new interface.
3.  **Synth**: Once `libfluidsynth-dev` is available in the env, implement `FluidSynthDriver`.

## Documentation
*   See `TECHNICAL_OVERVIEW.md` for architecture deep dive.
*   See `ROADMAP.md` for feature tracking.
*   See `AGENTS.md` for coding standards.
