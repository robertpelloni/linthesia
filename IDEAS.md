# IDEAS for Linthesia

This document contains a comprehensive, ambitious list of brainstormed features, architectural refactors, and conceptual pivots to drive the development of Linthesia from its current state into the future.

## 1. Architectural Refactoring & Porting
*   **WebAssembly (WASM) / WebGL Port**: Instead of restricting Linthesia to desktop platforms (Linux, macOS, Windows), compiling the core C++ engine via Emscripten into WebAssembly would allow the app to run seamlessly in any modern web browser.
    *   *Benefits*: Zero-installation onboarding.
    *   *Challenges*: Replacing ALSA MIDI driver with Web MIDI API.
*   **Modernizing the UI (Dear ImGui or Qt6)**: The current transition to GTKmm 3.0/Pango is heavily tied to legacy GTK architectures. Moving the UI entirely into immediate-mode rendering (e.g., Dear ImGui) would massively simplify the code, provide instantaneous multi-platform support, and look significantly more modern than the existing custom SDL2 buttons.
*   **Decoupling Engine and UI**: Extract the MIDI parsing, scoring, and playback synchronization logic into a purely headless library (`liblinthesia`). This would allow developers to write custom frontends (e.g., a pure CLI visualizer, or a VR piano game) using the exact same backend engine.

## 2. Advanced Feature Additions
*   **AI-Powered Hand Tracking (MediaPipe)**: Integrate a webcam feed and Google MediaPipe to track the user's fingers over a real acoustic piano, entirely eliminating the need for a digital MIDI keyboard to score hits!
*   **Procedural Sheet Music Generation Engine**: Expand the recently implemented `SheetMusicDisplay` from basic procedural notes into a full-fledged notation renderer (handling ties, slurs, lyrics, staccato marks, dynamics) or integrate an existing library like Verovio to render standard MEI/MusicXML directly alongside falling notes.
*   **Online Multiplayer Battle Mode**: "Piano Hero" online. Connect to a central server via WebSockets where multiple users compete on the same MIDI track simultaneously, sending their live timing accuracy metrics and streak combos to each other in real-time.
*   **Spotify/YouTube Audio Integration**: Instead of purely synthesizing MIDI files (which often sound artificial without multi-gigabyte sample libraries), synchronize the falling MIDI notes with the original streaming audio track of the song (similar to Rocksmith).

## 3. Quality of Life & Customization
*   **Custom Note Skins & Particle Systems**: Expose the textures for falling notes and the hit-sparks (`ParticleSystem`) so users can load their own custom graphics packages or mod the game.
*   **Interactive Tutorial & Chord Recognition**: If the user continually misses a specific complex chord, implement an "Intervention Mode" that pauses the game and provides a specific breakdown/fingering chart (e.g., "Use 1-3-5 here") before letting them continue.
*   **Virtual MIDI Output (DAW Integration)**: Allow Linthesia to output its internal auto-play tracks directly to a Virtual MIDI port, letting users route the falling notes directly into Ableton Live, FL Studio, or Logic Pro for extremely high-end VST rendering.

## 4. Project Pivots
*   **Pivot: Music Theory Curriculum Sandbox**: Shift from a pure "falling notes" game into a gamified music theory course. The software would generate randomized chord progressions, scales, and intervals on the fly, requiring the user to play them correctly to defeat enemies or progress through RPG-style levels.
*   **Pivot: Generative AI Co-Pilot**: Integrate an LLM or music generation model (like MusicLM or Audiocraft). If the user starts improvising during "Wait Mode", the system could analyze the key signature and mood, automatically generating an accompanying bassline or drum beat and rendering those notes on-screen dynamically. (Scaffolded `AICoPilot` module)

## 5. Omniscient Orchestration & Autonomous Agent Pipelines (Phase 4/5)
*   **LLM-Driven Refactoring (FastMCP)**: Now that `workspace_indexer.py` (FTS5 SQLite mapping) and `search_api.py` (FastMCP bridge) are stable, expand these tools to enable fully autonomous agent loops. The LLM can proactively use `analyze_dependencies` and `search_code_patterns` to mass-refactor C++ legacy patterns (like raw pointers to `std::unique_ptr`) without human supervision.
*   **Proactive CI Agent (`build_all.py`)**: Tie the FastMCP orchestrator directly into a Github Action that analyzes PR logic. If a commit breaks `build_all.py`, the AI should immediately clone the container, use the Search API to identify the dependency drift, and commit the fix automatically.
