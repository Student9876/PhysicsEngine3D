# CMakeList.txt : CMake project for PhysicsEngine3D

# Add source to this project's executable
add_executable(PhysicsEngine3D 
    "main.cpp"  
    "core/Object3D.cpp" 
    "core/camera.cpp" 
    "core/scene.cpp" 
    "rendering/renderer.cpp"  
    "rendering/Shader.cpp"
    "engine/Window.cpp" 
    "engine/Input.cpp" 
    "core/Block.cpp"
    "core/Light.cpp"
 "core/Sphere.cpp")

# Set C++ standard
set_property(TARGET PhysicsEngine3D PROPERTY CXX_STANDARD 20)
set_property(TARGET PhysicsEngine3D PROPERTY CXX_STANDARD_REQUIRED ON)

# Copy shader files to build directory with better path handling
if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/PhysicsEngine3D/Debug/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/PhysicsEngine3D/Release/)
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/PhysicsEngine3D/)
endif()

# Fetch dependencies with stable versions
include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)
FetchContent_MakeAvailable(glad)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link libraries to target
target_link_libraries(PhysicsEngine3D PRIVATE
    glfw
    glad
    glm::glm
    OpenGL::GL
)

# Include directories
target_include_directories(PhysicsEngine3D PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Windows-specific settings
if(WIN32)
    # Set subsystem to console for Windows
    set_target_properties(PhysicsEngine3D PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()