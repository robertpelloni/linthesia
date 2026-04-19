#!/usr/bin/env python3
import sqlite3
import os
import argparse
import sys
import json
from mcp.server.fastmcp import FastMCP

# This provides an MCP server wrapping the FTS5 table
# It can also be run as a CLI tool if arguments are provided.

DB_PATH = os.path.join(os.path.dirname(__file__), 'workspace_index.db')

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
