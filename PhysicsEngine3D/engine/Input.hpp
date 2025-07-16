#pragma once

#include <GLFW/glfw3.h>
#include "core/camera.hpp"

class Input {
public:
    static void initialize(GLFWwindow* window, Camera* cam);
    static void process(GLFWwindow* window, Camera& camera, float deltaTime);

private:
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static Camera* camera;
    static bool firstMouse;
    static float lastX;
    static float lastY;
};
