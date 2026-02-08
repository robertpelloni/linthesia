# Handoff Notes

## Current State
*   **Version**: 0.9.0
*   **Branch**: `feature-loop-practice-and-pause`
*   **Recent Features**: Interactive Pause Menu, Loop Practice (A-B Repeat), Unified Agent Docs.

## Next Steps
*   **Wait Mode Polish**: The "Learning" mode (wait for key) needs testing and polish, especially for chords.
*   **Scoring**: Implement a proper scoring system.
*   **Synth**: Investigate FluidSynth integration to remove external dependency.

## Notes for Next Agent
*   `PlayingState::Update` handles the game loop logic including metronome and looping.
*   `PlayingState::Draw` handles rendering.
*   `SettingsState` configures preferences.
*   **Constraint**: Cannot run `meson` build in this environment, rely on manual code verification.
