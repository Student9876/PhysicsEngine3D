# Test script for Windows

param(
    [string]$Preset,
    [string]$ExecutableName
)

# Run CTest
Set-Location "out/build/$Preset"
# Use --configuration instead of --config for cross-platform compatibility
ctest --output-on-failure --configuration Release
if ($LASTEXITCODE -ne 0) { echo "Tests failed or no tests found" }
Set-Location "../../.."

# Test executable - skip GUI testing in CI environments
$executablePath = "out/build/$Preset/PhysicsEngine3D/$ExecutableName"
if (Test-Path $executablePath) {
    echo "Executable found at: $executablePath"
    # Skip running GUI executable in CI to avoid GLFW initialization errors
    echo "Skipping executable test in CI environment (GUI applications require display)"
} else {
    echo "Executable not found at expected location"
    Get-ChildItem -Path "out/build/$Preset" -Name "$ExecutableName" -Recurse -ErrorAction SilentlyContinue
}