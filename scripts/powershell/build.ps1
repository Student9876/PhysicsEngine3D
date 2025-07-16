# Build script for Windows

param(
    [string]$Preset,
    [string]$VcpkgTriplet
)

# Ensure vcpkg is properly set up
if (-not $env:VCPKG_ROOT) {
    Write-Error "VCPKG_ROOT environment variable is not set"
    exit 1
}

# Install dependencies using vcpkg
Write-Host "Installing vcpkg dependencies for triplet: $VcpkgTriplet"
& "$env:VCPKG_ROOT/vcpkg.exe" install --triplet $VcpkgTriplet

# Configure with CMake
Write-Host "Configuring CMake with preset: $Preset"
cmake --preset $Preset -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=$VcpkgTriplet

# Build the project
Write-Host "Building project..."
cmake --build out/build/$Preset --config Release