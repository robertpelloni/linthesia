# Outstanding Issues & Short-Term Goals

- [x] Consolidate Dashboard UI layout into high-value prioritized tiers with rich tooltips and unified control surface (`dashboard.html`).
- [x] Integrate OS Tray Notification API and background daemon cycle hooks (`/api/tray/notify`, `/api/supervisor/cycle`).
- [x] Synchronize submodules and ensure zero drift across all 5 harness engines.
- [x] Complete GTKmm Rendering Transition (Phase 1): Abstract `TextWriter.cpp` to use Cairo/Pango for text rendering instead of `SDL_ttf`, outputting to OpenGL textures, preparing for the `Gtk::GLArea` swap.
- [x] Complete GTKmm Main Loop Integration (Phase 2): Migrate the core application event pump to `Gtk::Application` and `Glib::signal_timeout`.
- [x] Cross-Platform Audio Backends: Implement WinMM (Windows) and CoreMIDI (macOS) wrappers within `src/drivers/`.
- [x] Investigate AppImage/Flatpak: Provide a native Linux bundle.
- [x] Analyze Submodule Sync (Executive Protocol 59): Evaluated pianogame status. Verified stability and continued zero ABI drift.

- [x] Implement Headless Mode for liblinthesia decoupling
- [x] Implement basic WebSocket infrastructure in Go Backend
- [x] Investigate WASM / Emscripten Porting
