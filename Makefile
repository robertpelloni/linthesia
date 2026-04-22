.PHONY: all setup build test clean docs format lint run health

# Default target
all: build

# Setup the meson build directory
setup:
	@if [ ! -d "build" ]; then meson setup build; fi

# Build the project using ninja
build: setup
	@ninja -C build

# Run the test suite
test: build
	@ninja -C build test

# Clean the build directory
clean:
	@if [ -d "build" ]; then rm -rf build; fi
	@echo "Build directory cleaned."

# Generate/Update Documentation
docs: build
	@ninja -C build doc

# Format code using clang-format
format:
	@find src -iname "*.h" -o -iname "*.cpp" | xargs clang-format -i

# Lint code using clang-tidy
lint: build
	@find src -iname "*.cpp" | xargs clang-tidy -p build/compile_commands.json

# Run the application
run: build
	@./build/src/linthesia

# Run the workspace health monitor
health:
	@python3 scripts/health_check.py
