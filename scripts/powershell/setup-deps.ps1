# Dependency setup for Windows

if (!(Test-Path "vcpkg")) {
    git clone https://github.com/Microsoft/vcpkg.git
    .\vcpkg\bootstrap-vcpkg.bat
}

choco install ninja 7zip

echo "VCPKG_ROOT=$PWD\vcpkg" >> $env:GITHUB_ENV
echo "$PWD\vcpkg" >> $env:GITHUB_PATH