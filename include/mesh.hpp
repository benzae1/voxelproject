#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "shader.hpp"

class Mesh {
public:
    Mesh();
    ~Mesh();

    // Upload new vertex/index data to the GPU
    void update(const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices);

    // Render using current VAO
    void draw() const;

private:
    GLuint VAO, VBO, EBO;
    size_t indexCount;

    void setupMesh();
};

#endif
