#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Object3D {
public:
  Object3D(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 col = glm::vec3(1.0f));
  virtual ~Object3D();

  virtual void update(float deltaTime);
  virtual bool isSimulated() const;
  virtual void draw() const = 0;

  // Getters and setters for color
  glm::vec3 getColor() const { return color; }
  void setColor(const glm::vec3& col) { color = col; }

  glm::vec3 position;
  glm::vec3 size;
  glm::vec3 color;
  bool enablePhysics = false;
};