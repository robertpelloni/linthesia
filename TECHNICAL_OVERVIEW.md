# Technical Overview & Handover

This document provides a deep dive into the Linthesia architecture, recent changes (v1.2.x), and critical next steps for development.

## 1. Core Architecture

### 1.1 Game Loop (`src/main.cpp`)
*   **Initialization**: `SDL_Init`, `UserSetting::Initialize`, `MidiComm::midiInit`.
*   **Event Loop**: Polls `SDL_Event`, handles `SDL_QUIT`, `SDL_TEXTINPUT`, `SDL_KEYDOWN`.
*   **DrawingArea**: Wrapper around SDL window/glContext. Calls `state_manager->Update` and `Draw`.

### 1.2 State Management (`src/GameState.cpp`)
*   **GameStateManager**: Stack-based FSM. Manages the active `GameState`.
*   **GameState**: Abstract base class for screens.
    *   `TitleState`: Main menu.
    *   `SongLibState`: Song browser/search.
    *   `SettingsState`: Configuration.
    *   `PlayingState`: The core game.
    *   `StatsState`: Results screen.

### 1.3 MIDI Subsystem (`src/MidiComm.cpp` & `src/drivers/`)
*   **MidiDriver Interface**: (`src/MidiDriver.h`) Abstract base class for MIDI backends.
*   **AlsaMidiDriver**: (`src/drivers/AlsaMidiDriver.cpp`) Linux ALSA implementation.
*   **Global Instance**: `g_midi_driver` (in `MidiComm.cpp`) holds the active driver.
*   **MidiCommIn/Out**: Wrappers that use `g_midi_driver` to read/write events.

### 1.4 Persistence (`src/ScoreDB.cpp` & `src/UserSettings.cpp`)
*   **Settings**: Uses `Gio::Settings` (GSettings) via `gschema.xml`. Keys defined in `UserSettings.h`.
*   **Scores**: Uses `sqlite3`. Database created at `~/.local/linthesia/music.sqlite`. Stores scores, grades, and streaks.

## 2. Key Data Structures

### 2.1 Notes (`src/libmidi/Note.h`)
*   **Note**: Raw pulses from MIDI file.
*   **TranslatedNote**: Absolute timestamps (microseconds) based on tempo.
*   **NoteState**: `AutoPlayed`, `UserPlayable`, `UserHit`, `UserMissed`.

### 2.2 Statistics (`src/SharedState.h`)
*   `SongStatistics`: Aggregates score, hits (Perfect/Good), streaks, and max combo.

## 3. Recent Features (v1.2.x)

*   **Search**: `SongLibState` filters `m_song_tiles` based on `m_search_filter` (populated via `SDL_TEXTINPUT`).
*   **Loop Practice**: `PlayingState` tracks `m_loop_a` and `m_loop_b`. `Update` logic seeks back to A when B is reached.
*   **Wait Tolerance**: `m_wait_grace_timer` allows `Play()` to continue for 50-500ms after a blocking note to catch chords.
*   **Rhythm Mode**: `PlayingState::Listen` ignores pitch checks if `m_state.rhythm_mode` is true.

## 4. Known Gaps & Roadmap

### 4.1 Missing Features
*   **Sheet Music**: No rendering of standard notation. Needs a `SheetMusicDisplay` class.
*   **FluidSynth**: `AlsaMidiDriver` works, but requires an external synth (timidity/fluidsynth). Native integration is planned but blocked by missing dev libs in some envs.
*   **Windows/macOS**: `MidiDriver` interface exists, but `WinMidiDriver` (WinMM) and `CoreMidiDriver` are unimplemented.

### 4.2 Technical Debt
*   **MidiComm**: Still has some static lists (`notes_on`) that could be moved to the Driver or a Session object.
*   **Text Input**: `SongLibState` handles text well, but backspace handling is rudimentary (byte popping), which breaks UTF-8. Need a proper UTF-8 aware string handler.

## 5. Build Instructions
*   **System**: Linux (Debian/Ubuntu).
*   **Deps**: `libsdl2-dev`, `libsdl2-image-dev`, `libsdl2-ttf-dev`, `libasound2-dev`, `libsqlite3-dev`, `libgtkmm-3.0-dev`.
*   **Build**: `meson build && ninja -C build`.

## 6. Handover Note
The codebase is stable. Focus next on **Sheet Music** rendering logic (agnostic of graphics first) and **Cross-Platform** driver stubs.
