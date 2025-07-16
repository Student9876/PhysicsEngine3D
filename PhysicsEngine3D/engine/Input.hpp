#pragma once
#include <GLFW/glfw3.h>
#include "core/camera.hpp"

class Input {
public:
  static void initialize(GLFWwindow* window, Camera* camera);
  static void process(GLFWwindow* window, Camera& camera, float deltaTime);

private:
  static Camera* s_camera;
  static bool s_firstMouse;
  static float s_lastX;
  static float s_lastY;

  // GLFW callbacks
  static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};