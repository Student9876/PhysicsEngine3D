#pragma once
#include "core/Object3D.hpp"

class Sphere : public Object3D {
public:
  Sphere(glm::vec3 pos = glm::vec3(0.0f), float radius = 1.0f, int latitudeSegments = 32, int longitudeSegments = 32);
  ~Sphere();

  void draw() const override;

  // Sphere-specific getters/setters
  float getRadius() const { return radius; }
  void setRadius(float r) { radius = r; initMesh(); }

private:
  float radius;
  int latitudeSegments;
  int longitudeSegments;

  unsigned int VAO, VBO, EBO;
  int indexCount;

  void initMesh();
};