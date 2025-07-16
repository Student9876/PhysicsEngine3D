# CMakeList.txt : CMake project for PhysicsEngine3D

# Add source to this project's executable
add_executable(PhysicsEngine3D "main.cpp"  "core/Object3D.cpp" "core/camera.cpp" "core/scene.cpp" "rendering/renderer.cpp")

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PhysicsEngine3D PROPERTY CXX_STANDARD 20)
endif()

# Fetch dependencies

include(FetchContent)
# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(glad)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(glm)

# Link libraries to target
target_link_libraries(PhysicsEngine3D PRIVATE
  glfw
  glad
  glm
)

# Include directories
target_include_directories(PhysicsEngine3D PRIVATE
  ${glfw_SOURCE_DIR}/include
  ${glad_SOURCE_DIR}/include
  ${glm_SOURCE_DIR}
  thirdparty/glad-build/include
  ${CMAKE_CURRENT_SOURCE_DIR}

)
