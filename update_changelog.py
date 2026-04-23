import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.8] - 2026-04-23
### Changed
- **GTKmm Migration Phase 1 (Text Rendering)**: Successfully ripped out the legacy `SDL_ttf` dependency and rewrote `TextWriter.cpp` to use modern `Cairo` and `Pango` contexts for text rasterization. The text is now rendered onto an in-memory `Cairo::ImageSurface` and uploaded via standard OpenGL (`GL_BGRA`).

"""

content = content.replace("## [0.10.7] - 2026-04-22", new_entry + "## [0.10.7] - 2026-04-22")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
