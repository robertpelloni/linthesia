# Changelog

## [1.2.1] - 2024-05-22

### Added
- **Configurable Wait Tolerance**: Added a "Wait Tolerance" setting to the Advanced Settings menu, allowing users to adjust the chord grace period (0-500ms).
- **Audio Test**: Added a "Test Audio" button in Settings to verify MIDI output configuration.
- **Search UI**: Improved the song library search bar with a background box and blinking cursor visual.

### Changed
- **Polish**: Removed legacy TODO comments and improved code cleanliness.

## [1.2.0] - 2024-05-22

### Added
- **Rhythm Mode**: A new practice mode where pitch matching is disabled, allowing users to focus purely on rhythm/timing. Toggle with `F6` in the Track Selection screen.
- **Judgement Line**: Added a semi-transparent yellow line above the keys to indicate the exact timing window.
- **MidiDriver Integration**: Refactored the core MIDI communication layer (`MidiComm`) to use the new `MidiDriver` interface.

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
