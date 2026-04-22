import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.3] - 2026-04-20
### Added
- **Doxygen Integration**: Added a configured `Doxyfile` and a custom `doc` run target to `meson.build` to automatically generate C++ API documentation in `docs/api/html`. Output is ignored via `.gitignore` to prevent repo bloat.

"""

content = content.replace("## [0.10.2] - 2026-04-19", new_entry + "## [0.10.2] - 2026-04-19")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
