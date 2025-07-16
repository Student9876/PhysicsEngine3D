#include "engine/Input.hpp"
#include <iostream>

// Static member definitions
Camera* Input::s_camera = nullptr;
bool Input::s_firstMouse = true;
float Input::s_lastX = 640.0f; // Half of screen width
float Input::s_lastY = 360.0f; // Half of screen height

void Input::initialize(GLFWwindow* window, Camera* camera) {
  s_camera = camera;

  // Set input mode
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set callbacks
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetKeyCallback(window, keyCallback);
}

void Input::process(GLFWwindow* window, Camera& camera, float deltaTime) {
  // Process keyboard input
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(CameraMovement::LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.processKeyboard(CameraMovement::UP, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera.processKeyboard(CameraMovement::DOWN, deltaTime);
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
  if (!s_camera) return;

  if (s_firstMouse) {
    s_lastX = xpos;
    s_lastY = ypos;
    s_firstMouse = false;
  }

  float xoffset = xpos - s_lastX;
  float yoffset = s_lastY - ypos; // Reversed since y-coordinates go from bottom to top

  s_lastX = xpos;
  s_lastY = ypos;

  s_camera->processMouseMovement(xoffset, yoffset);
}

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  if (!s_camera) return;
  s_camera->processMouseScroll(yoffset);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // Handle ESC key to close window
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  // Toggle cursor mode with TAB
  if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
    static bool cursorEnabled = false;
    cursorEnabled = !cursorEnabled;
    glfwSetInputMode(window, GLFW_CURSOR,
      cursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
  }
}