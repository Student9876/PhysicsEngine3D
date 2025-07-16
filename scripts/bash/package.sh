#!/bin/bash
# Common packaging script for Linux/macOS

set -e

PRESET=$1
EXECUTABLE_NAME=$2
ASSET_NAME=$3

mkdir -p release
cp "out/build/$PRESET/PhysicsEngine3D/$EXECUTABLE_NAME" release/

# Copy any required shared libraries
find "out/build/$PRESET" \( -name "*.so" -o -name "*.dylib" \) -print0 | xargs -0 -I {} cp {} release/ 2>/dev/null || true

chmod +x "release/$EXECUTABLE_NAME"
tar -czf "$ASSET_NAME.tar.gz" -C release .