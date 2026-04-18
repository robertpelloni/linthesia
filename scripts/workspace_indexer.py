#!/usr/bin/env python3
import os
import sqlite3
import fnmatch

# Database path
DB_PATH = os.path.join(os.path.dirname(__file__), 'workspace_index.db')

# Files to include/exclude
INCLUDE_PATTERNS = ['*.cpp', '*.h', '*.c', '*.cc', '*.py', '*.md', '*.txt', '*.xml', '*.json', 'meson.build', 'Makefile']
EXCLUDE_DIRS = ['.git', 'build', 'node_modules', 'venv', '.env', 'music', 'graphics', 'po']

def init_db():
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    # Create FTS5 virtual table for ultra-fast full-text searching
    c.execute('''
        CREATE VIRTUAL TABLE IF NOT EXISTS file_index USING fts5(
            path,
            content
        )
    ''')
    # Clear existing data on re-index
    c.execute('DELETE FROM file_index')
    conn.commit()
    return conn

def should_index(filename):
    for pattern in INCLUDE_PATTERNS:
        if fnmatch.fnmatch(filename, pattern):
            return True
    return False

def index_workspace(root_dir, conn):
    c = conn.cursor()
    indexed_count = 0

    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Modify dirnames in-place to skip excluded directories
        dirnames[:] = [d for d in dirnames if d not in EXCLUDE_DIRS]

        for filename in filenames:
            if should_index(filename):
                filepath = os.path.join(dirpath, filename)
                rel_path = os.path.relpath(filepath, root_dir)

                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        content = f.read()

                    c.execute('INSERT INTO file_index (path, content) VALUES (?, ?)', (rel_path, content))
                    indexed_count += 1
                except UnicodeDecodeError:
                    # Skip binary files that slip through or have weird encodings
                    pass
                except Exception as e:
                    print(f"Error reading {rel_path}: {e}")

    conn.commit()
    return indexed_count

if __name__ == '__main__':
    root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
    print(f"Initializing workspace index database at {DB_PATH}")
    conn = init_db()

    print(f"Scanning workspace: {root} ...")
    count = index_workspace(root, conn)

    print(f"Successfully indexed {count} files.")
    conn.close()
