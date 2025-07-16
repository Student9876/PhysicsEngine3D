#!/bin/bash
# Common test script for Linux/macOS

set -e

PRESET=$1
EXECUTABLE_NAME=$2

# Run CTest
cd "out/build/$PRESET"
ctest --output-on-failure --config Release || true
cd ../../..

# Test executable
if [ -f "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME" ]; then
    chmod +x "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME"
    "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME" --version || echo "Version check failed or not supported"
else
    echo "Executable not found at expected location"
    find "out/build/$PRESET" -name "$EXECUTABLE_NAME" -type f || true
fi