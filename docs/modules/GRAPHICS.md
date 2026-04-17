# Graphics Module Documentation

The Graphics module in Linthesia abstracts the rendering pipeline, supporting multiple backend technologies while providing a consistent drawing API for all `GameState` implementations. The project is actively transitioning from raw SDL2/OpenGL rendering to a GTKmm/Pango hybrid approach.

## Architecture

The module uses an object-oriented approach to decouple high-level drawing commands (e.g., `DrawQuad`, `DrawText`) from the underlying graphics library.

### Core Components

#### 1. `OSGraphics` (`src/OSGraphics.h/cpp`)
The lowest-level system abstraction layer for graphics initialization.
*   **Key Responsibilities**:
    *   Creates and destroys the main application window (currently transitioning from `SDL_Window` to GTKmm equivalents).
    *   Initializes OpenGL context.
    *   Handles window resizing and fullscreen toggling.
    *   Swaps the rendering buffers (`SwapBuffers`).

#### 2. `Renderer` (`src/Renderer.h/cpp`)
The central drawing interface used by all game states.
*   **Key Responsibilities**:
    *   Maintains the active rendering state (current color, projection matrix).
    *   Provides primitives for drawing shapes (`DrawQuad`, `DrawLine`).
    *   Renders images/textures (`DrawTga`).
    *   Calculates and sets the orthographic projection for 2D UI rendering.
*   **API Methods**:
    *   `void SetColor(Color c);`
    *   `void DrawQuad(int x, int y, int w, int h);`
    *   `void DrawTga(Tga *tga, int x, int y);`
*   **Custom Structs**:
    *   `Color`: A simple `(r, g, b, a)` structure replacing `SDL_Color` to prevent conflicts during the GTKmm transition. Instantiated via `Renderer::ToColor(r, g, b, a)`.

#### 3. `Tga` (`src/Tga.h/cpp`)
The image asset management class. Linthesia primarily uses uncompressed TGA files for textures to avoid external dependencies like libpng.
*   **Key Responsibilities**:
    *   Loads and parses `.tga` files from the filesystem.
    *   Uploads pixel data to the GPU (OpenGL textures).
    *   Manages OpenGL texture IDs.
    *   Provides `Draw()` methods to bind and render the texture to screen coordinates.

#### 4. `TextWriter` (`src/TextWriter.h/cpp`)
The high-level text rendering class, which is the primary focus of the GTKmm/Pango transition.
*   **Key Responsibilities**:
    *   Renders dynamic text strings using TrueType fonts.
    *   Currently relies on Pango contexts (e.g., `PGContext`) to calculate layouts and rasterize text, blending it into the SDL2/OpenGL pipeline.

## Data Flow
1.  **State Execution**: A `GameState` (e.g., `PlayingState`) is updated and requested to render.
2.  **Drawing**: The state calls methods on the `Renderer` instance (e.g., `renderer.DrawQuad()`).
3.  **Rasterization**:
    *   *Primitives*: The `Renderer` issues raw OpenGL immediate mode commands (`glBegin(GL_QUADS)`, `glVertex2i()`).
    *   *Textures*: The state calls `GetTexture(Enum)`, which returns a `Tga` object. The state then calls `tga->Draw()`, which binds the texture (`glBindTexture`) and issues OpenGL quad commands.
    *   *Text*: The state instantiates a `TextWriter`, which uses Pango to rasterize text and render it via the `Renderer`.
4.  **Display**: The main loop calls `OSGraphics::SwapBuffers()` to present the rendered frame to the user.

## GTKmm Transition Notes
The project is moving away from raw SDL2 rendering for the UI. Currently, the `Renderer` constructor accepts GTKmm `GLContext` and `PGContext` objects. These are initialized as dummies in `main.cpp` (`Renderer rend(GLContext(), PGContext());`) to allow compilation while the full GTKmm event loop integration is being completed.
