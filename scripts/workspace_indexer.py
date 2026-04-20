#!/usr/bin/env python3
import os
import sqlite3
import fnmatch
import subprocess
import concurrent.futures
import argparse
from collections import defaultdict

# Database path
DB_PATH = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'workspace_search_index.db')

# Files to include/exclude
INCLUDE_PATTERNS = ['*.py', '*.js', '*.ts', '*.java', '*.cpp', '*.c', '*.h', '*.cs', '*.go', '*.rs', '*.md', '*.txt', '*.xml', '*.json', 'meson.build', 'Makefile', '*.tsx', '*.yaml', '*.yml']
EXCLUDE_DIRS = ['.git', 'build', 'node_modules', 'venv', '.env', 'music', 'graphics', 'po']

def init_db():
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()

    # Metadata table to store last modified times and indexed commit hashes
    c.execute('''
        CREATE TABLE IF NOT EXISTS file_metadata (
            path TEXT PRIMARY KEY,
            mtime REAL
        )
    ''')
    c.execute('''
        CREATE TABLE IF NOT EXISTS commit_metadata (
            hash TEXT PRIMARY KEY
        )
    ''')

    # Create FTS5 virtual table for ultra-fast full-text searching
    c.execute('''
        CREATE VIRTUAL TABLE IF NOT EXISTS file_index USING fts5(
            path,
            content
        )
    ''')
    c.execute('''
        CREATE VIRTUAL TABLE IF NOT EXISTS commit_index USING fts5(
            hash,
            author,
            date,
            message
        )
    ''')
    conn.commit()
    return conn

def should_index(filename):
    for pattern in INCLUDE_PATTERNS:
        if fnmatch.fnmatch(filename, pattern):
            return True
    return False

def index_commits(root_dir, conn, full_reindex=False):
    c = conn.cursor()
    indexed_count = 0

    if full_reindex:
         c.execute('DELETE FROM commit_index')
         c.execute('DELETE FROM commit_metadata')
         indexed_hashes = set()
    else:
        # Get previously indexed hashes
        c.execute('SELECT hash FROM commit_metadata')
        indexed_hashes = {row[0] for row in c.fetchall()}

    try:
        # Get log in format: hash|author|date|message
        result = subprocess.run(
            ['git', 'log', '--pretty=format:%H|%an|%ad|%s', '--date=iso'],
            cwd=root_dir, stdout=subprocess.PIPE, text=True, check=True
        )
        for line in result.stdout.split('\n'):
            parts = line.split('|', 3)
            if len(parts) == 4:
                commit_hash = parts[0]
                if commit_hash not in indexed_hashes:
                    c.execute('INSERT INTO commit_index (hash, author, date, message) VALUES (?, ?, ?, ?)', parts)
                    c.execute('INSERT INTO commit_metadata (hash) VALUES (?)', (commit_hash,))
                    indexed_count += 1
        conn.commit()
    except Exception as e:
        print(f"Error indexing commits: {e}")
    return indexed_count

def read_file_content(filepath, root_dir):
    rel_path = os.path.relpath(filepath, root_dir)
    mtime = os.path.getmtime(filepath)
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
        return rel_path, content, mtime
    except UnicodeDecodeError:
        return rel_path, None, mtime
    except Exception as e:
        print(f"Error reading {rel_path}: {e}")
        return rel_path, None, mtime

def index_workspace(root_dir, conn, full_reindex=False):
    c = conn.cursor()
    indexed_count = 0
    file_paths = []

    if full_reindex:
         c.execute('DELETE FROM file_index')
         c.execute('DELETE FROM file_metadata')
         metadata = {}
    else:
        # Get current metadata
        c.execute('SELECT path, mtime FROM file_metadata')
        metadata = dict(c.fetchall())

    current_files = set()

    for dirpath, dirnames, filenames in os.walk(root_dir):
        dirnames[:] = [d for d in dirnames if d not in EXCLUDE_DIRS]
        for filename in filenames:
            if should_index(filename):
                full_path = os.path.join(dirpath, filename)
                rel_path = os.path.relpath(full_path, root_dir)
                current_files.add(rel_path)
                mtime = os.path.getmtime(full_path)

                # Check if file is new or modified
                if full_reindex or rel_path not in metadata or metadata[rel_path] < mtime:
                     file_paths.append(full_path)

    # Delete removed files from index
    files_to_remove = set(metadata.keys()) - current_files
    for rel_path in files_to_remove:
        c.execute("DELETE FROM file_index WHERE path = ?", (rel_path,))
        c.execute("DELETE FROM file_metadata WHERE path = ?", (rel_path,))

    # Parallel processing for file reads
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = {executor.submit(read_file_content, fp, root_dir): fp for fp in file_paths}
        for future in concurrent.futures.as_completed(futures):
            rel_path, content, mtime = future.result()
            if content is not None:
                # Remove existing entry if updating
                if rel_path in metadata and not full_reindex:
                    c.execute("DELETE FROM file_index WHERE path = ?", (rel_path,))
                c.execute('INSERT INTO file_index (path, content) VALUES (?, ?)', (rel_path, content))
                c.execute('INSERT OR REPLACE INTO file_metadata (path, mtime) VALUES (?, ?)', (rel_path, mtime))
                indexed_count += 1

    conn.commit()
    return indexed_count

def generate_dashboard():
    if not os.path.exists(DB_PATH):
        print("Error: Index database not found. Please index first.")
        return

    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    try:
        c.execute('SELECT path FROM file_index')
        counts = defaultdict(int)
        for row in c.fetchall():
            path = row[0]
            parts = path.split(os.sep)
            # Group by top-level directory/submodule (if in a dir) or root
            if len(parts) > 1:
                module = parts[0]
            else:
                module = "<root>"
            counts[module] += 1

        print("=== Workspace Index Dashboard ===")
        print(f"{'Submodule/Directory':<30} | {'Indexed Files'}")
        print("-" * 50)
        for module, count in sorted(counts.items()):
            print(f"{module:<30} | {count}")
    except sqlite3.Error as e:
        print(f"Database error: {e}")
    finally:
        conn.close()

def search_index(query, limit=10, fuzzy=False):
    if not os.path.exists(DB_PATH):
        print("Error: Index database not found. Please index first.")
        return

    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    try:
        # Properly escape quotes if using MATCH syntax
        safe_query = query.replace("'", "''")

        if fuzzy:
             # FTS5 basic prefix matching approach for "fuzzy"
             match_clause = f"'{safe_query}*'"
        else:
             match_clause = f"'{safe_query}'"

        c.execute(f'''
            SELECT
                path,
                snippet(file_index, 1, '[MATCH]', '[/MATCH]', '...', 64) as snippet
            FROM file_index
            WHERE file_index MATCH {match_clause}
            ORDER BY rank
            LIMIT {limit}
        ''')
        results = c.fetchall()
        if not results:
             print(f"No results found for '{query}'.")
        else:
             print(f"Found {len(results)} results for '{query}':\n")
             for row in results:
                  print(f"--- {row[0]} ---")
                  print(row[1])
                  print("\n")
    except sqlite3.Error as e:
        print(f"Database error: {e}")
    finally:
        conn.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Workspace Indexer and Search CLI")
    parser.add_argument('action', nargs='?', choices=['index', 'search', 'reindex', 'dashboard'], default='index', help='Action to perform: index (incremental), reindex (full), search, or dashboard')
    parser.add_argument('query', nargs='?', type=str, help='Query to search for (if action is search)')
    parser.add_argument('--limit', type=int, default=10, help='Maximum search results to return')
    parser.add_argument('--fuzzy', action='store_true', help='Use prefix matching for fuzzy search')

    args = parser.parse_args()

    root = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))

    if args.action in ('index', 'reindex'):
        full_reindex = (args.action == 'reindex')
        print(f"Initializing workspace index database at {DB_PATH}")
        conn = init_db()

        print(f"Scanning workspace files: {root} (Full Reindex: {full_reindex})...")
        file_count = index_workspace(root, conn, full_reindex)

        print(f"Scanning workspace commits: {root} ...")
        commit_count = index_commits(root, conn, full_reindex)

        print(f"Successfully indexed {file_count} new/modified files and {commit_count} new commits.")
        conn.close()
    elif args.action == 'search':
        if not args.query:
             print("Please provide a search query: python scripts/workspace_indexer.py search <query>")
        else:
             search_index(args.query, args.limit, args.fuzzy)
    elif args.action == 'dashboard':
        generate_dashboard()
