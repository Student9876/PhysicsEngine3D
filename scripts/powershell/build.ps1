# Build script for Windows

param(
    [string]$Preset,
    [string]$VcpkgTriplet
)

cmake --preset $Preset -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=$VcpkgTriplet

cmake --build out/build/$Preset --config Release