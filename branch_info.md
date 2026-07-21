Branch name: jules-gtkmm-migration
Title: Phase 2 and 3 GTKmm Migration
Description: This commit completes Phase 2 and Phase 3 of the GTKmm migration protocol. It abstracts keyboard mapping logic into `KeyMapper`, generic event handling into `InputManager`, and introduces a native `MainWindow` that relies on `Gtk::GLArea` to provide the OpenGL context. `SDL_Window` and legacy event loops have been cleanly removed from `src/main.cpp`. Build configuration was updated to support the new dependencies.
Commit Message: feat: Phase 2 and 3 GTKmm migration (Input Abstraction and Window Swap)

- Created KeyMapper.h/cpp to map PC keyboard to MIDI notes (supporting QWERTY, AZERTY, QWERTZ).
- Created InputManager.h/cpp to abstract UI events via GDK signals instead of SDL_Event polling.
- Created MainWindow.h/cpp inheriting from Gtk::Window and using Gtk::GLArea for the main game window context and render loop.
- Updated main.cpp to remove SDL_Window and the infinite while loop in favor of Gtk::Application::run().
- Integrated new modules into meson.build and verified tests across the workspace.
