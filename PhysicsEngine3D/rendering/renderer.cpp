#include "rendering/renderer.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height) {
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::clear() const {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::resize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, screenWidth, screenHeight);
}

void Renderer::draw(const Object3D& object, const Camera& camera) const {
    // Placeholder: In future, this will bind VAO, use shader, apply MVP matrices
    object.draw();

    std::cout << "Drawing object at position: "
        << object.position.x << ", "
        << object.position.y << ", "
        << object.position.z << std::endl;
}
