# Contributing to Linthesia

First off, thank you for considering contributing to Linthesia! It's people like you that make open-source development such a rewarding community.

The following is a set of guidelines for contributing to Linthesia and its submodules. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

## Code of Conduct
This project and everyone participating in it is governed by the Linthesia Code of Conduct. By participating, you are expected to uphold this code.

## Getting Started

### 1. Build Environment
Linthesia uses the Meson build system alongside Ninja. To get started on a Linux environment (Ubuntu/Debian):

```bash
sudo apt-get update
sudo apt-get install -y build-essential meson ninja-build libtool-bin
sudo apt-get install -y libasound2-dev libgl1-mesa-dev libglibmm-2.4-dev \
                        libsqlite3-dev libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev \
                        gettext doxygen libgtest-dev
```

### 2. Compiling
Use the provided `Makefile` which acts as a wrapper around Meson:
```bash
make build
make test
```

## How Can I Contribute?

### Reporting Bugs
This section guides you through submitting a bug report. Following these guidelines helps maintainers and the community understand your report, reproduce the behavior, and find related reports.
*   **Use the issue search** — check if the issue has already been reported.
*   **Check if the issue has been fixed** — try to reproduce it using the latest `main` branch.
*   Provide a clear and descriptive title.
*   Include the exact steps to reproduce the problem.
*   Provide the version of Linthesia and your operating system.

### Suggesting Enhancements
This section guides you through submitting an enhancement suggestion, including completely new features and minor improvements to existing functionality.
*   Review our `IDEAS.md` and `ROADMAP.md` files first to see if your idea is already planned.
*   Provide a detailed description of the suggested enhancement.
*   Explain why this enhancement would be useful to most users.

### Pull Requests
The process described here has several goals:
- Maintain Linthesia's quality
- Fix problems that are important to users
- Engage the community in working toward the best possible open-source piano visualizer

1.  **Fork the repo and create your branch from `main`.**
2.  If you've added code that should be tested, **add tests** (see `tests/` directory and Google Test framework).
3.  If you've changed APIs, update the documentation. (Our `meson.build` has a `doc` target that runs Doxygen).
4.  Ensure the test suite passes (`make test`).
5.  Format your code using the provided `.clang-format` file.
6.  Issue that pull request!

## Architecture Overview
Please read `docs/ARCHITECTURE.md` and `TECHNICAL_OVERVIEW.md` before making sweeping changes. The project relies on a separation of concerns between `libmidi` (backend logic) and `GameState` (frontend rendering).

## Updating the Workspace Index
We use an intelligent FTS5 SQLite indexer to allow for rapid navigation across the codebase. If you are adding entirely new modules or making massive file changes, run:
```bash
./update_docs.sh
```

## Versioning
Linthesia uses a single source of truth for versioning: the `VERSION` file in the root directory. Do not hardcode versions in the source files. Ensure that the `CHANGELOG.md` is updated according to the Keep a Changelog standard whenever you bump the version.
