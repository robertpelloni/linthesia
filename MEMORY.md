# Developer Memory

## Architectural Decisions
*   **MidiDriver**: Abstraction introduced to decouple ALSA. `AlsaMidiDriver` handles Linux IO. Future drivers (WinMM, CoreMIDI, FluidSynth) should implement `MidiDriver`.
*   **SheetMusicDisplay**: Procedural rendering chosen over sprite-based for Clefs/Accidentals to allow scaling and flexibility without external assets.
*   **Persistence**: SQLite chosen for robustness. Defaults to `~/.local/share/linthesia/scores.db`.

## Known Issues / Quirks
*   **Text Rendering**: `TextWriter` uses `SDL_ttf`. Currently hardcoded to `FreeSans.ttf` in some places.
*   **Wait Mode**: The grace period logic is in `PlayingState`. Visual indicator is planned.
*   **Input**: `KeyBackspace` was added to `GameKey` enum for Search support.

## Preferences
*   **UI**: Prefer "Tango" color palette (defined in `TrackProperties.h`).
*   **Code**: Keep `GameState` logic separate from `Renderer` details where possible.
