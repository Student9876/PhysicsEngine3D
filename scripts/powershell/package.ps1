# Packaging script for Windows

param(
    [string]$Preset,
    [string]$ExecutableName,
    [string]$AssetName
)

New-Item -ItemType Directory -Force -Path release
Copy-Item "out\build\$Preset\PhysicsEngine3D\$ExecutableName" -Destination release\

# Copy any required DLLs
Get-ChildItem "out\build\$Preset" -Filter "*.dll" -Recurse | Copy-Item -Destination release\

Compress-Archive -Path release\* -DestinationPath "$AssetName.zip"