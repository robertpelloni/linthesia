# GTKmm Transition Guide

The roadmap mandates transitioning the application from raw SDL2 to a GTKmm/Pango native environment.
However, after deep architectural analysis, this transition requires a foundational rewrite of the application's lifecycle, rendering pipeline, and event handling.

## Challenges with Immediate Transition

1. **`main.cpp` Event Loop**: The entire `GameLoop` is driven by `SDL_PollEvent`. Replacing this requires integrating `Gtk::Application::run()`, which takes over the main thread.
2. **OpenGL Contexts**: The game relies on `SDL_GL_CreateContext` and raw immediate mode OpenGL (`glBegin`, `glEnd`). GTKmm uses `Gtk::GLArea`, which provides its own context via signals (`on_render(const Glib::RefPtr<Gdk::GLContext>&)`). `Renderer` needs to be rewritten to accept and utilize this specific context.
3. **Text Rendering**: `TextWriter.cpp` heavily relies on `SDL_ttf` (`TTF_RenderText_Blended`) to generate `SDL_Surface`s which are then manually pushed to OpenGL textures. Moving to Pango means using `Pango::Layout` and Cairo to render to an image surface, extracting the pixels, and uploading to OpenGL.
4. **Input Mapping**: `src/main.cpp` manually maps `SDL_SCANCODE`s to internal `GameKey`s. This massive switch statement needs to be ported to `GdkEventKey` hardware keycodes.

## Recommended Path Forward

Because this is such a massive and highly destructive refactor, it should be done in a dedicated Phase rather than as a "short term goal" in a single session.

### Phase 1: Text Rendering Abstraction (Pango + Cairo)
Replace `SDL_ttf` inside `TextWriter.cpp` with a Cairo/Pango rendering backend that outputs a raw RGBA buffer, which is then uploaded to the existing SDL-managed OpenGL context. This removes the `SDL_ttf` dependency without breaking the windowing system.

### Phase 2: Input Abstraction
Extract the SDL event polling into a generic `InputManager` class.

### Phase 3: Windowing Swap
Finally, replace `SDL_Window` with `Gtk::Window` and `Gtk::GLArea`, piping the GTK signals into the generic `InputManager` and triggering the `GameStateManager->Draw()` call from within `GLArea::on_render`.

For now, the dummy contexts `Renderer rend(GLContext(nullptr), PGContext(nullptr));` will remain in place to maintain stability while the underlying systems are prepared.
