#!/bin/bash
# Common dependency setup for Linux/macOS

set -e

if [[ "$RUNNER_OS" == "Linux" ]]; then
    sudo apt-get update
    sudo apt-get install -y build-essential cmake ninja-build pkg-config \
        libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
        libgl1-mesa-dev libglu1-mesa-dev
elif [[ "$RUNNER_OS" == "macOS" ]]; then
    brew install cmake ninja pkg-config
fi

# Setup vcpkg
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/Microsoft/vcpkg.git
    chmod +x vcpkg/bootstrap-vcpkg.sh
    ./vcpkg/bootstrap-vcpkg.sh
fi

echo "VCPKG_ROOT=$PWD/vcpkg" >> "$GITHUB_ENV"
echo "$PWD/vcpkg" >> "$GITHUB_PATH"