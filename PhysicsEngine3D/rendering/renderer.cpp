#include "rendering/renderer.hpp"
#include "rendering/Shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height) {
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    initializeShaders();
}

Renderer::~Renderer() = default;

void Renderer::initializeShaders() {
    try {
        basicShader = std::make_unique<Shader>("PhysicsEngine3D/shaders/basic.vert", 
                                              "PhysicsEngine3D/shaders/basic.frag");
    } catch (const std::exception& e) {
        std::cerr << "Failed to load shaders: " << e.what() << std::endl;
        // Fallback to default OpenGL pipeline
    }
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

glm::mat4 Renderer::getProjectionMatrix() const {
    return glm::perspective(glm::radians(45.0f), 
                           (float)screenWidth / (float)screenHeight, 
                           0.1f, 100.0f);
}

void Renderer::draw(const Object3D& object, const Camera& camera) const {
    if (basicShader) {
        basicShader->use();
        
        // Create transformation matrices
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, object.position);
        model = glm::scale(model, object.size);
        
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = getProjectionMatrix();
        
        // Set uniforms
        basicShader->setMat4("model", model);
        basicShader->setMat4("view", view);
        basicShader->setMat4("projection", projection);
        basicShader->setVec3("objectColor", glm::vec3(0.8f, 0.3f, 0.2f));
        basicShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    }
    
    object.draw();
}
