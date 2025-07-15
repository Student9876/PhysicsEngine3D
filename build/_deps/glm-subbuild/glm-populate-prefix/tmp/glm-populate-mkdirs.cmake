# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-src")
  file(MAKE_DIRECTORY "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-src")
endif()
file(MAKE_DIRECTORY
  "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-build"
  "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix"
  "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix/tmp"
  "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
  "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix/src"
  "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Project/CPP/PhysicsEngine3D/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
