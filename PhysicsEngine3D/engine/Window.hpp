#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    GLFWwindow* getGLFWwindow() const;
    void setResizeCallback(std::function<void(int, int)> callback);

private:
    GLFWwindow* window;
    static std::function<void(int, int)> resizeCallback;
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
