#include "rendering/renderer.hpp"
#include "rendering/Shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <filesystem>

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height) {
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    initializeShaders();
}

Renderer::~Renderer() = default;

void Renderer::initializeShaders() {
    try {
        // Try multiple shader paths for cross-platform compatibility
        std::vector<std::string> shaderPaths = {
            "shaders/basic.vert",
            "PhysicsEngine3D/shaders/basic.vert",
            "../PhysicsEngine3D/shaders/basic.vert",
            "../../PhysicsEngine3D/shaders/basic.vert"
        };
        
        std::string vertPath, fragPath;
        bool found = false;
        
        for (const auto& basePath : shaderPaths) {
            std::string testVert = basePath;
            std::string testFrag = basePath;
            testFrag.replace(testFrag.find(".vert"), 5, ".frag");
            
            if (std::filesystem::exists(testVert) && std::filesystem::exists(testFrag)) {
                vertPath = testVert;
                fragPath = testFrag;
                found = true;
                break;
            }
        }
        
        if (found) {
            basicShader = std::make_unique<Shader>(vertPath, fragPath);
            std::cout << "Shaders loaded successfully from: " << vertPath << std::endl;
        } else {
            std::cerr << "Could not find shader files in any of the expected locations" << std::endl;
        }
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
    basicShader->setVec3("objectColor", object.color);  // Use object's color
    basicShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    // You might also want to add these for proper lighting:
    basicShader->setVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    basicShader->setVec3("viewPos", camera.position);
  }

  object.draw();
}
