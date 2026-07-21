1. **Repository Synchronization**:
   - Update FTS5 index utilizing `python3 scripts/workspace_indexer.py`.

2. **Input Integration**:
   - Update `GameState.h` and `GameState.cpp` to include `"libmidi/MidiEvent.h"` and add a `virtual void OnMidiEvent(const MidiEvent& ev) {}` method to `GameState`.
   - Update `GameStateManager` to add `void OnMidiEvent(const MidiEvent& ev)` which forwards the event to `m_current_state->OnMidiEvent(ev)` if `m_current_state` is active.
   - Update `InputManager.cpp` to include `"libmidi/MidiEvent.h"`. In `OnKeyPress`, if `note >= 0`, create a `MidiEvent ev = MidiEvent::Build(MidiEventSimple(0x90, note, 127));` and pass it to `m_state_manager->OnMidiEvent(ev)`. Similarly, in `OnKeyRelease`, create a `MidiEvent` with type `0x80` and velocity `0`, and pass it to `m_state_manager->OnMidiEvent(ev)`. Remove `SendNoteOff(note)` from `InputManager.cpp` if bypassing ALSA. Let's keep `sendNote` functionality as well to still trigger hardware lights if desired, but prioritize injecting into `m_state_manager`.
   - Update `PlayingState.h` and `PlayingState.cpp` to override `OnMidiEvent(const MidiEvent& ev)` and process the synthetic event. I will extract the core matching/scoring logic from `Listen` into a reusable private method `ProcessEvent(const MidiEvent& ev)` and call it from both `Listen` and `OnMidiEvent`.

3. **Verify Modifications**:
   - Use `cat` on `src/GameState.h`, `src/GameState.cpp`, `src/InputManager.cpp`, `src/PlayingState.h` and `src/PlayingState.cpp` to verify the logic correctly bridges the PC keyboard directly into the backend scoring mechanism.

4. **Testing**:
   - Execute `make build` to verify compilation.
   - Run the full test suite using `python3 build_all.py` to verify stability across the monorepo.

5. **Pre-commit Steps**:
   - Complete pre-commit steps to ensure proper testing, verification, review, and reflection are done.

6. **Submit**:
   - Commit the changes and push.
