# Changelog

## [1.2.0] - 2024-05-22

### Added
- **Rhythm Mode**: A new practice mode where pitch matching is disabled, allowing users to focus purely on rhythm/timing. Toggle with `F6` in the Track Selection screen.
- **Judgement Line**: Added a semi-transparent yellow line above the keys to indicate the exact timing window.
- **MidiDriver Integration**: Refactored the core MIDI communication layer (`MidiComm`) to use the new `MidiDriver` interface, fully isolating ALSA dependencies into `src/drivers/AlsaMidiDriver.cpp`.

### Changed
- **Internal**: `MidiComm` no longer calls ALSA directly. It uses the global `g_midi_driver` instance.

## [1.1.0] - 2024-05-22

### Added
- **Score Persistence**: Implemented a local SQLite database to save song scores, grades, and streaks.
- **Library Assessment**: The Song Library now displays your best score and grade for each song directly on the tile.
- **MidiDriver**: Created `AlsaMidiDriver` class as part of the cross-platform refactoring effort.
- **Advanced Scoring**: Added Streak tracking with visual popups (every 10 hits) and "S"/"SS" ranks for high accuracy.

## [1.0.0] - 2024-05-22

### Added
- **Song Search**: Users can now type to search for songs in the library. Added Backspace support for text editing.
- **Wait Mode Tolerance**: "Learning" mode now has a 50ms grace period to handle "rolled" chords or sloppy MIDI files without stuttering.
- **SDL Text Input**: Integrated SDL2 text input event handling into the game engine.

### Changed
- **Version**: Bumped to 1.0.0, marking feature completeness for the core Linux scope.
- **Documentation**: Updated Roadmap to reflect 1.0 status.
