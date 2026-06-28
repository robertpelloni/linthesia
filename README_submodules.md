# Submodules Overview

## 1. `pianogame`
* **Path**: `/pianogame`
* **Status**: Static / Frozen.
* **Purpose**: This submodule serves as the foundational reference codebase (Synthesia 0.6.1a) from which Linthesia was forked. It acts as an archival artifact and ABI reference.
* **WASM Impact**: Because it relies heavily on native Win32/macOS desktop hooks, it will not be part of the Emscripten WASM build pipeline. Web compilation is strictly limited to the decoupled `liblinthesia` engine in the parent repository.
