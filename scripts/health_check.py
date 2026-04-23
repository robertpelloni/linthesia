#!/usr/bin/env python3
import os
import subprocess
import sys
import json
import argparse
from datetime import datetime, timezone

# Define critical system dependencies using pkg-config names
SYSTEM_DEPENDENCIES = [
    "alsa",
    "gl",
    "giomm-2.4",
    "gtkmm-3.0",
    "sqlite3",
    "sdl2",

    "SDL2_image",
    "fluidsynth",
    "gtest"
]

def check_command(cmd, cwd=None):
    """Run a shell command and return boolean success and output."""
    try:
        result = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
        return True, result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return False, e.stderr.strip()
    except FileNotFoundError:
        return False, "Command not found"

def check_dependencies():
    """Verify all system dependencies using pkg-config."""
    results = {}
    all_passed = True
    for dep in SYSTEM_DEPENDENCIES:
        passed, output = check_command(['pkg-config', '--exists', dep])
        if passed:
            _, version = check_command(['pkg-config', '--modversion', dep])
            results[dep] = {"status": "OK", "version": version}
        else:
            results[dep] = {"status": "MISSING", "error": output}
            all_passed = False
    return all_passed, results

def check_submodules(root_dir):
    """Check if git submodules are initialized and up to date."""
    passed, output = check_command(['git', 'submodule', 'status'], cwd=root_dir)
    if not passed:
        return False, {"error": output}

    modules = {}
    all_passed = True
    if output:
        for line in output.split('\n'):
            if line:
                # Format: " hash path (describe)" or "-hash path" (uninitialized) or "+hash path" (out of sync)
                status_char = line[0]
                parts = line[1:].split()
                path = parts[1] if len(parts) > 1 else "Unknown"
                if status_char == '-':
                    modules[path] = "UNINITIALIZED"
                    all_passed = False
                elif status_char == '+':
                    modules[path] = "OUT_OF_SYNC"
                    all_passed = False
                else:
                    modules[path] = "OK"
    else:
        modules["status"] = "No submodules configured"

    return all_passed, modules

def check_build_status(root_dir):
    """Check if the project has been built successfully."""
    build_dir = os.path.join(root_dir, 'build')
    results = {
        "build_dir_exists": os.path.isdir(build_dir),
        "executable_exists": os.path.isfile(os.path.join(build_dir, 'src', 'linthesia')),
        "tests_passed": False
    }

    if results["executable_exists"]:
        # Try running tests via ninja if build exists
        passed, _ = check_command(['ninja', '-C', build_dir, 'test'])
        results["tests_passed"] = passed

    all_passed = results["build_dir_exists"] and results["executable_exists"] and results["tests_passed"]
    return all_passed, results

def generate_report(format_json=False):
    root_dir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))

    dep_passed, dep_results = check_dependencies()
    sub_passed, sub_results = check_submodules(root_dir)
    build_passed, build_results = check_build_status(root_dir)

    overall_health = dep_passed and sub_passed and build_passed

    report = {
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "overall_health": "HEALTHY" if overall_health else "DEGRADED",
        "components": {
            "dependencies": {
                "healthy": dep_passed,
                "details": dep_results
            },
            "submodules": {
                "healthy": sub_passed,
                "details": sub_results
            },
            "build_status": {
                "healthy": build_passed,
                "details": build_results
            }
        }
    }

    if format_json:
        print(json.dumps(report, indent=2))
    else:
        print("="*50)
        print(f"  WORKSPACE HEALTH MONITOR - {report['overall_health']}")
        print("="*50)
        print(f"Time: {report['timestamp']}\n")

        print("--- SYSTEM DEPENDENCIES ---")
        for dep, info in dep_results.items():
            if info['status'] == 'OK':
                print(f"  [OK] {dep:<15} v{info.get('version', 'unknown')}")
            else:
                print(f"  [!!] {dep:<15} MISSING")

        print("\n--- SUBMODULES ---")
        for sub, status in sub_results.items():
            if status == "OK":
                print(f"  [OK] {sub}")
            else:
                print(f"  [!!] {sub:<15} {status}")

        print("\n--- BUILD STATUS ---")
        print(f"  Build Directory: {'[OK]' if build_results['build_dir_exists'] else '[!!] Missing'}")
        print(f"  Executable:      {'[OK]' if build_results['executable_exists'] else '[!!] Missing'}")
        print(f"  Test Suite:      {'[OK]' if build_results['tests_passed'] else '[!!] Failing or Not Run'}")
        print("="*50)

    return 0 if overall_health else 1

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Live Health Monitoring Script")
    parser.add_argument('--json', action='store_true', help="Output report in JSON format")
    args = parser.parse_args()

    sys.exit(generate_report(args.json))
