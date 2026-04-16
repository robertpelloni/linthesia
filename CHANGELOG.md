# Changelog

All notable changes to Linthesia will be documented in this file.

## [0.9.3] - 2026-04-15
### Added
- **UI/UX Polish**: Upgraded tooltip verbosity across Settings and Track Selection screens for improved clarity. Added in-game Pause menu controls legend.

- **Sight Reading**: Implemented `SheetMusicDisplay` for standard Grand Staff notation toggled via F7.
- **Wait Mode Grace Period**: Added a wait tolerance logic to the Learning Mode (Wait Mode) with the `WAIT_TOLERANCE_KEY` to allow grace periods for rolled chords and non-quantized MIDI notes.
- **Scoring System**: Perfect, Good, Miss, and Streak combos and popup indicators.

## [0.9.1] - 2026-04-12
### Added
- **UI/UX Polish**: Upgraded tooltip verbosity across Settings and Track Selection screens for improved clarity. Added in-game Pause menu controls legend.

- **Song Library Search**: Added text-based search functionality to the Song Library screen. Users can now type characters to filter the currently displayed list of MIDI files and directories. Backspace works.

### Fixed
- Fixed critical syntax and logic regressions introduced in the previous mass-replace process across `PlayingState.cpp`, `main.cpp`, and `FileSelector.cpp`.
- Resolved merge conflict markers and successfully migrated the Github Actions CI workflow to use `actions/checkout@v4` with the necessary `libgtkmm-3.0-dev` dependency for Pango rendering contexts.

## [0.9.0] - Prior Work
- Basic state management transitions.
- Preliminary GTKmm/Pango graphics backend transition setup.
- Custom `Color` structure to replace `SDL_Color` for better cross-compatibility.
