#!/usr/bin/env python3

import os
import subprocess
import sys

def run_command(command, cwd=None):
    print(f"Running: {' '.join(command)} in {cwd or os.getcwd()}")
    result = subprocess.run(command, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    if result.returncode != 0:
        print(f"Command failed with exit code {result.returncode}")
        print(result.stdout)
        return False
    print("Success.")
    return True

def find_projects(root_dir):
    node_projects = []
    python_projects = []
    cpp_projects = []

    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Skip common ignored directories
        if any(ignored in dirpath.split(os.sep) for ignored in ['node_modules', '.git', 'build', 'venv', '.env']):
            continue

        if 'package.json' in filenames:
            node_projects.append(dirpath)
        if 'requirements.txt' in filenames or 'setup.py' in filenames:
            python_projects.append(dirpath)
        if 'meson.build' in filenames and dirpath == root_dir: # Main C++ project
            cpp_projects.append(dirpath)

    return node_projects, python_projects, cpp_projects

def build_node(project_dir):
    print(f"\\n--- Building Node.js project in {project_dir} ---")
    if not run_command(['npm', 'install'], cwd=project_dir):
        return False
    if not run_command(['npm', 'run', 'build', '--if-present'], cwd=project_dir):
        return False
    if not run_command(['npm', 'test', '--if-present'], cwd=project_dir):
        return False
    return True

def build_python(project_dir):
    print(f"\\n--- Building Python project in {project_dir} ---")
    if 'requirements.txt' in os.listdir(project_dir):
        if not run_command(['pip', 'install', '-r', 'requirements.txt'], cwd=project_dir):
            return False
    # If there's a test directory or file, try running pytest or unittest
    if os.path.exists(os.path.join(project_dir, 'tests')):
        if not run_command(['python3', '-m', 'unittest', 'discover', 'tests'], cwd=project_dir):
            return False
    return True

def build_cpp(project_dir):
    print(f"\\n--- Building C++ project in {project_dir} ---")
    if not run_command(['make', 'build'], cwd=project_dir):
        return False
    if not run_command(['make', 'test'], cwd=project_dir):
        return False
    return True

def main():
    root_dir = os.path.abspath(os.path.dirname(__file__))
    print(f"Scanning workspace: {root_dir}")

    node_projects, python_projects, cpp_projects = find_projects(root_dir)

    print(f"Found {len(node_projects)} Node.js projects.")
    print(f"Found {len(python_projects)} Python projects.")
    print(f"Found {len(cpp_projects)} C++ projects.")

    success = True

    for cpp in cpp_projects:
        if not build_cpp(cpp):
            success = False

    for node in node_projects:
        if not build_node(node):
            success = False

    for python in python_projects:
        if not build_python(python):
            success = False

    if success:
        print("\\nWorkspace build verification complete: ALL SUCCESSFUL.")
        sys.exit(0)
    else:
        print("\\nWorkspace build verification complete: ERRORS DETECTED.")
        sys.exit(1)

if __name__ == '__main__':
    main()
