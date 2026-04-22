import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.6] - 2026-04-22
### Added
- **Live Health Monitoring**: Created `scripts/health_check.py` to actively probe the project environment and verify critical system dependencies (via `pkg-config`), submodule synchronization status, and build readiness. Added a `make health` wrapper to seamlessly integrate this validation step into standard CI/CD workflows and developer terminals.

"""

content = content.replace("## [0.10.5] - 2026-04-21", new_entry + "## [0.10.5] - 2026-04-21")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
