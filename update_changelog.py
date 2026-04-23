import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.10] - 2026-04-23
### Changed
- **Submodule & Orchestration Sync**: Fully verified the frozen upstream `pianogame` repository constraints. Flushed the FTS5 search index via `update_docs.sh` and pushed all codebase modifications seamlessly to maintain `HEALTHY` multi-agent CI/CD statuses. Prepared `HANDOFF.md` outlining GTKmm Phase 2 (Input Abstraction) constraints.

"""

content = content.replace("## [0.10.9] - 2026-04-23", new_entry + "## [0.10.9] - 2026-04-23")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
