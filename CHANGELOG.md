# Changelog

## [0.8.0] - 2024-05-22

### Added
- **Settings Menu**: New "Advanced Settings" menu in the title screen.
  - Configure **Lead-In Time**: Adjust the delay before a song starts.
  - Configure **Lead-Out Time**: Adjust the delay after a song ends.
  - Configure **Scroll Speed** (Visible Duration): Control how fast notes fall.
  - **Metronome**: Toggle a visual metronome (flashing indicator on beat).
- **In-Game Help**: Pressing 'Space' to pause now displays a help overlay with a list of all controls.
- **Visual Metronome**: A yellow indicator flashes in the top-right corner on every beat when enabled.
- **Version Consolidation**: Project version is now read from a single `VERSION` file.

### Changed
- **Volume Controls**: Swapped Keypad `+` and `-` mappings. `+` now increases volume, and `-` decreases it (fixing counter-intuitive behavior).
- **Documentation**: Completely rewrote `README.md` to serve as a comprehensive user manual.
- **Build System**: Updated `meson.build` to read version from `VERSION` file.
- **Settings Storage**: New settings are persisted using GSettings/Glib.

### Fixed
- Fixed volume control direction on keypad.
