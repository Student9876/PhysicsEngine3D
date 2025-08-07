// Updated main.cpp with integrated Light system
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
#include "core/Light.hpp"
#include <vector>
#include <memory>

int screenWidth = 1280;
int screenHeight = 720;

// Global lights for easy access
std::vector<Light> sceneLights;

void setupLights(Renderer& renderer) {
  // Create a sun-like directional light
  Light sun = Light::createSun(
    glm::vec3(-0.3f, -0.8f, -0.5f), // Direction
    glm::vec3(1.0f, 0.95f, 0.8f),   // Color
    1.0f                            // Brightness
  );
  sun.setPosition(glm::vec3(0.0f, 5.0f, 0.0f)); // Place sun above scene
  sun.setBrightness(1.2f);                      // Increase brightness
  sun.setIntensity(1.0f);                       // Set intensity
  // If you have a glow property, set it as well



  // Create some point lights for variety
  Light pointLight1 = Light::createPointLight(
    glm::vec3(2.0f, 1.0f, 2.0f),     // Position
    glm::vec3(0.8f, 0.4f, 0.2f),     // Orange color
    0.8f                              // Brightness
  );

  Light pointLight2 = Light::createPointLight(
    glm::vec3(-2.0f, 1.0f, -2.0f),   // Position
    glm::vec3(0.2f, 0.4f, 0.8f),     // Blue color
    0.6f                              // Brightness
  );

  // Create a spotlight
  Light spotlight = Light::createSpotlight(
    glm::vec3(0.0f, 5.0f, 0.0f),     // Position (above scene)
    glm::vec3(0.0f, -1.0f, 0.0f),    // Direction (pointing down)
    glm::vec3(1.0f, 1.0f, 1.0f),     // White color
    1.0f,                             // Brightness
    12.5f,                            // Inner cutoff (degrees)
    17.5f                             // Outer cutoff (degrees)
  );

  // Add lights to the scene
  sceneLights.push_back(sun);
  //sceneLights.push_back(pointLight1);
  //sceneLights.push_back(pointLight2);
  //sceneLights.push_back(spotlight);

  // Set lights in renderer
  renderer.setLights(sceneLights);
}

void updateLights(float deltaTime, Renderer& renderer) {
  // Make the sun orbit around the scene
  static float sunOrbitSpeed = 0.2f;
  sceneLights[0].orbit(glm::vec3(0.0f, 0.0f, 0.0f), 8.0f, sunOrbitSpeed, deltaTime);

  // Make point lights move
  static float time = 0.0f;
  time += deltaTime;

  // Oscillate point light positions
  //sceneLights[1].setPosition(glm::vec3(
  //  2.0f * sin(time * 0.5f),
  //  1.0f + 0.5f * sin(time * 2.0f),
  //  2.0f * cos(time * 0.5f)
  //));

  //sceneLights[2].setPosition(glm::vec3(
  //  -2.0f * sin(time * 0.3f),
  //  1.0f + 0.3f * cos(time * 1.5f),
  //  -2.0f * cos(time * 0.3f)
  //));

  // Update brightness based on sun position (day/night cycle)
  /*float sunHeight = sceneLights[0].getPosition().y;
  float dayBrightness = glm::clamp((sunHeight + 2.0f) / 4.0f, 0.1f, 1.2f);
  sceneLights[0].setBrightness(dayBrightness);*/

  // Update lights in renderer
  renderer.setLights(sceneLights);
}

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

  // Setup lighting system
  setupLights(renderer);

  // Add one block (cube)
  auto cube = std::make_shared<Block>(glm::vec3(-2.0f, -2.0f, -2.0f));
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

    // Update lighting system
    //updateLights(deltaTime, renderer);

    scene.update(deltaTime);   // physics placeholder
    scene.render(renderer);    // draw everything

    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
  }

  return 0;
}