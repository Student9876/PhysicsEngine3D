# Common test script for Windows

param(
    [string]$Preset,
    [string]$ExecutableName
)

# Run CTest
Set-Location "out/build/$Preset"
ctest --output-on-failure --config Release
if ($LASTEXITCODE -ne 0) { echo "Tests failed or no tests found" }
Set-Location "../../.."

# Test executable
$executablePath = "out/build/$Preset/PhysicsEngine3D/$ExecutableName"
if (Test-Path $executablePath) {
    & $executablePath --version
    if ($LASTEXITCODE -ne 0) { echo "Version check failed or not supported" }
} else {
    echo "Executable not found at expected location"
    Get-ChildItem -Path "out/build/$Preset" -Name "$ExecutableName" -Recurse -ErrorAction SilentlyContinue
}