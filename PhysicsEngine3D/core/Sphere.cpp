#include "core/Sphere.hpp"
#include <glad/glad.h>
#include <cmath>
#include <vector>


const float M_PI = 3.14159265358979323846f; // Define PI if not already defined


Sphere::Sphere(glm::vec3 pos, float radius, int latitudeSegments, int longitudeSegments)
  : Object3D(pos), radius(radius), latitudeSegments(latitudeSegments),
  longitudeSegments(longitudeSegments), VAO(0), VBO(0), EBO(0), indexCount(0) {
  initMesh();
}

Sphere::~Sphere() {
  if (VAO != 0) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }
}

void Sphere::initMesh() {
  // Clean up existing buffers if they exist
  if (VAO != 0) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  // Generate vertices
  for (int lat = 0; lat <= latitudeSegments; ++lat) {
    float theta = lat * M_PI / latitudeSegments; // 0 to PI
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    for (int lon = 0; lon <= longitudeSegments; ++lon) {
      float phi = lon * 2.0f * M_PI / longitudeSegments; // 0 to 2*PI
      float sinPhi = sin(phi);
      float cosPhi = cos(phi);

      // Position (scaled by radius)
      float x = radius * cosPhi * sinTheta;
      float y = radius * cosTheta;
      float z = radius * sinPhi * sinTheta;

      // Normal (normalized position for unit sphere)
      float nx = cosPhi * sinTheta;
      float ny = cosTheta;
      float nz = sinPhi * sinTheta;

      // Add vertex data: position (3) + normal (3) = 6 floats per vertex
      vertices.insert(vertices.end(), {
          x, y, z,        // Position
          nx, ny, nz      // Normal
        });
    }
  }

  // Generate indices
  for (int lat = 0; lat < latitudeSegments; ++lat) {
    for (int lon = 0; lon < longitudeSegments; ++lon) {
      int first = lat * (longitudeSegments + 1) + lon;
      int second = first + longitudeSegments + 1;

      // First triangle
      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(first + 1);

      // Second triangle
      indices.push_back(second);
      indices.push_back(second + 1);
      indices.push_back(first + 1);
    }
  }

  indexCount = indices.size();

  // Generate and bind VAO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  // Bind and fill VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  // Bind and fill EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

  // Position attribute (location 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Normal attribute (location 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Sphere::draw() const {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}