#!/usr/bin/env python3
import sqlite3
import os
import argparse
import sys
import json
from mcp.server.fastmcp import FastMCP

# This provides an MCP server wrapping the FTS5 table
# It can also be run as a CLI tool if arguments are provided.

DB_PATH = os.path.join(os.path.dirname(__file__), '..', 'workspace_index.db')

# Create the FastMCP server
mcp = FastMCP("WorkspaceIndexer")

@mcp.tool()
def search_workspace(query: str, limit: int = 10) -> str:
    """
    Search the entire workspace for a specific query using SQLite FTS5.
    Returns file paths and snippets of matching code.
    """
    if not os.path.exists(DB_PATH):
        return "Error: Index database not found. Please run workspace_indexer.py first."

    try:
        conn = sqlite3.connect(DB_PATH)
        c = conn.cursor()

        # Use FTS5 MATCH syntax for full-text search
        c.execute('''
            SELECT
                path,
                snippet(file_index, 1, '[MATCH]', '[/MATCH]', '...', 64) as snippet
            FROM file_index
            WHERE file_index MATCH ?
            ORDER BY rank
            LIMIT ?
        ''', (query, limit))

        results = c.fetchall()
        conn.close()

        if not results:
            return f"No results found for '{query}'."

        output = f"Found {len(results)} results for '{query}':\n\n"
        for row in results:
            output += f"--- {row[0]} ---\n{row[1]}\n\n"

        return output

    except sqlite3.Error as e:
        return f"Database error: {str(e)}"


@mcp.tool()
def search_commits(query: str, limit: int = 10) -> str:
    """
    Search the workspace commit history using SQLite FTS5.
    Returns commit hashes, authors, dates, and messages.
    """
    if not os.path.exists(DB_PATH):
        return "Error: Index database not found. Please run workspace_indexer.py first."

    try:
        conn = sqlite3.connect(DB_PATH)
        c = conn.cursor()

        c.execute('''
            SELECT
                hash, author, date, message,
                snippet(commit_index, 3, '[MATCH]', '[/MATCH]', '...', 64) as snippet
            FROM commit_index
            WHERE commit_index MATCH ?
            ORDER BY rank
            LIMIT ?
        ''', (query, limit))

        results = c.fetchall()
        conn.close()

        if not results:
            return f"No commits found matching '{query}'."

        output = f"Found {len(results)} commits matching '{query}':\n\n"
        for row in results:
            output += f"Commit: {row[0]}\nAuthor: {row[1]}\nDate: {row[2]}\nMessage: {row[3]}\nSnippet: {row[4]}\n\n"

        return output

    except sqlite3.Error as e:
        return f"Database error: {str(e)}"


import re

@mcp.tool()
def search_code_patterns(regex_pattern: str, limit: int = 10) -> str:
    """
    Pattern matching for specific code constructs across the workspace.
    Uses regex to scan all indexed files. Extremely powerful for finding specific logic flows.
    Note: Since SQLite FTS5 doesn't natively support full PCRE regex across the entire index efficiently,
    this pulls all paths and contents and filters them in Python. Use with caution on massive repos.
    """
    if not os.path.exists(DB_PATH):
        return "Error: Index database not found."

    try:
        conn = sqlite3.connect(DB_PATH)
        c = conn.cursor()
        c.execute('SELECT path, content FROM file_index')

        matches = []
        try:
            pattern = re.compile(regex_pattern)
        except re.error as e:
            return f"Invalid regex pattern: {e}"

        for row in c.fetchall():
            path, content = row
            if content:
                for match in pattern.finditer(content):
                    # Get surrounding context
                    start = max(0, match.start() - 30)
                    end = min(len(content), match.end() + 30)
                    snippet = content[start:end].replace('\n', ' ')
                    matches.append(f"--- {path} ---\n...{snippet}...")
                    if len(matches) >= limit:
                        break
            if len(matches) >= limit:
                break

        conn.close()

        if not matches:
            return f"No regex matches found for '{regex_pattern}'."

        return f"Found matches for '{regex_pattern}':\n\n" + "\n\n".join(matches)

    except sqlite3.Error as e:
        return f"Database error: {str(e)}"

@mcp.tool()
def analyze_dependencies(project_path: str = "") -> str:
    """
    Cross-project dependency analysis.
    Searches for `#include` (C++), `import` (Python/JS/TS), and `require` statements across files
    to map out which files depend on what.
    """
    if not os.path.exists(DB_PATH):
        return "Error: Index database not found."

    try:
        conn = sqlite3.connect(DB_PATH)
        c = conn.cursor()

        # Simple FTS query to find files containing import keywords
        query = 'include OR import OR require'
        if project_path:
            c.execute('SELECT path, content FROM file_index WHERE path LIKE ? AND file_index MATCH ? LIMIT 100', (f'%{project_path}%', query))
        else:
            c.execute('SELECT path, content FROM file_index WHERE file_index MATCH ? LIMIT 100', (query,))

        deps = {}
        include_pattern = re.compile(r'^#include\s+["<](.*?)[">]', re.MULTILINE)
        import_pattern = re.compile(r'^(?:from\s+([\w.]+)\s+)?import\s+([\w., ]+)', re.MULTILINE)

        for row in c.fetchall():
            path, content = row
            if not content: continue

            file_deps = []
            if path.endswith(('.cpp', '.h', '.c', '.cc')):
                file_deps.extend(include_pattern.findall(content))
            elif path.endswith('.py'):
                for match in import_pattern.finditer(content):
                    module = match.group(1) or match.group(2)
                    file_deps.append(module.strip())

            if file_deps:
                deps[path] = list(set(file_deps))

        conn.close()

        if not deps:
            return "No dependencies found."

        output = "Dependency Analysis:\n\n"
        for path, dependencies in deps.items():
            output += f"File: {path}\n  Depends on: {', '.join(dependencies)}\n\n"

        return output

    except sqlite3.Error as e:
        return f"Database error: {str(e)}"

if __name__ == '__main__':
    # If arguments are provided, run as CLI, otherwise run as MCP server
    if len(sys.argv) > 1:
        parser = argparse.ArgumentParser(description="Workspace Search API (CLI or MCP backend)")
        parser.add_argument('query', type=str, help="FTS5 search query")
        parser.add_argument('--limit', type=int, default=10, help="Maximum number of results to return")
        args = parser.parse_args()

        print(search_workspace(args.query, args.limit))
    else:
        # Run as MCP server using stdio
        mcp.run(transport='stdio')
