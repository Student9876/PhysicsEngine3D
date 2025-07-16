cmake_minimum_required(VERSION 3.10)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project("PhysicsEngine3D")

add_subdirectory("PhysicsEngine3D")


set(CMAKE_DISABLE_FIND_PACKAGE_Doxygen TRUE)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(VCPKG_DISABLE_METRICS TRUE)
