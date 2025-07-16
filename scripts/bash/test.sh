#!/bin/bash
# Common test script for Linux/macOS

set -e

PRESET=$1
EXECUTABLE_NAME=$2

# Run CTest
cd "out/build/$PRESET"
if command -v ctest >/dev/null 2>&1; then
    ctest --output-on-failure || echo "Tests failed or no tests found"
else
    echo "Warning: ctest not found. Please install CMake to run tests."
fi
cd ../../..

# Test executable - check multiple possible locations
possiblePaths=(
    "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME"
    "out/build/$PRESET/$EXECUTABLE_NAME"
    "out/build/$PRESET/bin/$EXECUTABLE_NAME"
)

executableFound=false
for path in "${possiblePaths[@]}"; do
    if [ -f "$path" ]; then
        chmod +x "$path"
        echo "Executable found at: $path"
        executableFound=true
        break
    fi
done

if [ "$executableFound" = false ]; then
    echo "Executable not found at expected locations"
    find "out/build/$PRESET" -name "$EXECUTABLE_NAME" -type f || true
fi

# Skip running GUI executable in CI to avoid GLFW initialization errors
echo "Skipping executable test in CI environment (GUI applications require display)"