#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

// Forward declarations
class Shader;
class Object3D;
class Camera;
class Light;

class Renderer {
public:
  Renderer(int width, int height);
  ~Renderer();

  void clear() const;
  void resize(int width, int height);
  void draw(const Object3D& object, const Camera& camera) const;

  // Light management
  void setLights(const std::vector<Light>& lights);
  void addLight(const Light& light);
  void clearLights();

  glm::mat4 getProjectionMatrix() const;

private:
  int screenWidth, screenHeight;
  std::unique_ptr<Shader> basicShader;
  std::vector<Light> lights;

  void initializeShaders();
  void setLightUniforms(const Shader& shader) const;
};