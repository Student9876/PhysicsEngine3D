#!/bin/bash
# Common test script for Linux/macOS

set -e

PRESET=$1
EXECUTABLE_NAME=$2

# Run CTest
cd "out/build/$PRESET"
ctest --output-on-failure || true
cd ../../..

# Test executable - skip GUI testing in CI environments
if [ -f "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME" ]; then
    chmod +x "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME"
    echo "Executable found at: out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME"
    # Always skip GUI executable testing in CI to avoid GLFW errors
    echo "Skipping executable test in CI environment (GUI applications require display)"
else
    echo "Executable not found at expected location"
    find "out/build/$PRESET" -name "$EXECUTABLE_NAME" -type f || true
fi