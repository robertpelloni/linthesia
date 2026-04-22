import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.7] - 2026-04-22
### Changed
- **Workspace Indexer Validation**: Acknowledged a secondary system prompt to implement `workspace_indexer.py`. Verified that the existing script (implemented in earlier phases) already satisfies the rigorous requirements of FTS5 search across all federated submodules.

"""

content = content.replace("## [0.10.6] - 2026-04-22", new_entry + "## [0.10.6] - 2026-04-22")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
