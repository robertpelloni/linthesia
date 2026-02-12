# Changelog

## [1.3.0-dev] - 2024-05-22

### Added
- **Sheet Music Rendering**: Created `SheetMusicDisplay` class capable of rendering a music staff and mapping MIDI notes to visual positions (initial implementation).

## [1.2.1] - 2024-05-22

### Added
- **Configurable Wait Tolerance**: Added a "Wait Tolerance" setting to the Advanced Settings menu.
- **Audio Test**: Added a "Test Audio" button in Settings.
- **Search UI**: Improved the song library search bar.

### Changed
- **Polish**: Fixed PC keyboard audio regression.

## [1.2.0] - 2024-05-22

### Added
- **Rhythm Mode**: A new practice mode where pitch matching is disabled.
- **Judgement Line**: Added a visual timing aid.
- **MidiDriver Integration**: Refactored `MidiComm` to use `MidiDriver`.
