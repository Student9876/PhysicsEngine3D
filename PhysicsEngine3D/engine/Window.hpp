#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    GLFWwindow* getGLFWwindow() const;

private:
    GLFWwindow* window;
};
