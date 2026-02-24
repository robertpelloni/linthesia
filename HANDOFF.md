# Handoff Note

**To:** Next AI Agent (Claude, Gemini, or Jules)
**From:** Jules
**Date:** 2024-05-22
**Version:** 1.9.0-dev

## Current Status
Linthesia is now feature-rich with advanced notation, persistence, and improved usability for PC users.

### Accomplishments
1.  **PC Keyboard Gameplay**: Users can now play the game using their PC keyboard without needing an external MIDI device. This was achieved by injecting simulated MIDI events into the game loop (`MidiCommIn::Inject`, `PlayingState::OnMidiEvent`).
2.  **Visual Polish**: Menu transitions (Fade to Black) implemented in `GameStateManager`.
3.  **Security**: Fixed a buffer overflow in `main.cpp` regarding DB path.
4.  **Sheet Music Phase 3**: Grand Staff, Bass Clef, Accidentals.
5.  **Educational Features**: Note Labels on falling notes, Wait Mode Indicator.

### Known Issues
*   **FluidSynth**: Not implemented due to missing `libfluidsynth-dev`.
*   **Text Rendering**: `SDL_ttf` usage is basic.
*   **Input Mapping**: PC Keyboard mapping is hardcoded in `main.cpp` (QWERTY layout). A remapping UI is desired.

## Next Steps (Priorities)
1.  **Input Mapping UI**: Allow users to remap PC keys.
2.  **Visual Polish**: Add background images/animations to Title Screen.
3.  **Cross-Platform**: Test/Implement Windows support.

## Useful Commands
*   **Build**: `meson compile -C build`
*   **Run**: `./build/src/linthesia`
*   **Docs**: Read `AGENTS.md` first.
