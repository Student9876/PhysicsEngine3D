#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "engine/Window.hpp"
#include "engine/Input.hpp"
#include "core/camera.hpp"
#include <iostream>
#include "core/scene.hpp"
#include "core/Block.hpp"
#include "rendering/renderer.hpp"
#include "core/Sphere.hpp"


int screenWidth = 1280;
int screenHeight = 720;

int main() {
  // Create OpenGL context window
  Window window(screenWidth, screenHeight, "PhysicsEngine3D");
  GLFWwindow* glfwWindow = window.getGLFWwindow();

  // Camera setup - use shared_ptr from the start
  auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
  Input::initialize(glfwWindow, camera.get()); // Pass raw pointer to Input

  // Scene and Renderer
  Scene scene;
  Renderer renderer(screenWidth, screenHeight);

  // Set the same camera instance for the scene
  scene.setCamera(camera);

  // Add one block (cube)
  auto cube = std::make_shared<Block>(glm::vec3(0.0f, 0.0f, 0.0f));
  scene.addObject(cube);





  // Add spheres
  auto sphere1 = std::make_shared<Sphere>(glm::vec3(3.0f, 0.0f, 0.0f), 1.0f, 32, 32, glm::vec3(1.0f, 0.2f, 0.2f));
  scene.addObject(sphere1);

  auto sphere2 = std::make_shared<Sphere>(glm::vec3(0.0f, 2.0f, 0.0f), 0.5f, 16, 16, glm::vec3(0.2f, 1.0f, 0.2f));
  scene.addObject(sphere2);

  auto sphere3 = std::make_shared<Sphere>(glm::vec3(0.0f, -2.0f, 0.0f), 0.5f, 24, 24, glm::vec3(0.2f, 0.2f, 1.0f));
  scene.addObject(sphere3);



  // Timing
  float lastFrame = 0.0f;
  float deltaTime = 0.0f;

  // Main loop
  while (!glfwWindowShouldClose(glfwWindow)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process input with the same camera instance
    Input::process(glfwWindow, *camera, deltaTime);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.update(deltaTime);   // physics placeholder
    scene.render(renderer);    // draw everything

    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
  }

  return 0;
}