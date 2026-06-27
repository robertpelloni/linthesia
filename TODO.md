# Outstanding Issues & Short-Term Goals

- [x] Complete GTKmm Rendering Transition (Phase 1): Abstract `TextWriter.cpp` to use Cairo/Pango for text rendering instead of `SDL_ttf`, outputting to OpenGL textures, preparing for the `Gtk::GLArea` swap.
- [x] Cross-Platform Audio Backends: Implement WinMM (Windows) and CoreMIDI (macOS) wrappers within `src/drivers/`.
- [x] Investigate AppImage/Flatpak: Provide a native Linux bundle.
- [x] Analyze Submodule Sync (Executive Protocol 59): Evaluated pianogame status. Verified stability and continued zero ABI drift.

- [x] Implement Headless Mode for liblinthesia decoupling
- [ ] Implement basic WebSocket infrastructure in Go Backend
- [ ] Investigate WASM / Emscripten Porting
