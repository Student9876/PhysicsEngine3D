#pragma once

#include "core/Object3D.hpp"
#include "core/camera.hpp"
#include "rendering/Shader.hpp"
#include <memory>

class Renderer {
public:
    Renderer(int screenWidth, int screenHeight);
    ~Renderer();

    void clear() const;
    void draw(const Object3D& object, const Camera& camera) const;
    void resize(int width, int height);
    
    // Get projection matrix for external use
    glm::mat4 getProjectionMatrix() const;

private:
    int screenWidth;
    int screenHeight;
    std::unique_ptr<Shader> basicShader;
    
    void initializeShaders();
};
