import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.5] - 2026-04-21
### Changed
- **GTKmm Migration Plan**: Evaluated the ongoing GTKmm graphics transition. Determined that replacing `SDL_Window` and `SDL_ttf` with `Gtk::GLArea` and `Pango` represents a foundational rewrite of the core event loop. Created `README_GTK_MIGRATION.md` to break this down into discrete, testable phases (Phase 5/6) rather than a single destabilizing commit.

"""

content = content.replace("## [0.10.4] - 2026-04-20", new_entry + "## [0.10.4] - 2026-04-20")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
