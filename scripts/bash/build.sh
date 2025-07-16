#!/bin/bash
# Common build script for Linux/macOS

set -e

PRESET=$1
VCPKG_TRIPLET=$2
BUILD_TYPE=${3:-Release}

# Configure
cmake --preset "$PRESET" \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DVCPKG_TARGET_TRIPLET="$VCPKG_TRIPLET"

# Build
cmake --build "out/build/$PRESET" --config "$BUILD_TYPE"