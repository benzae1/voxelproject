#pragma once
#include <vector>
#include "mesh.hpp"
#include <glm/glm.hpp>

class Chunk {
public:
    static constexpr int SIZE_X = 16;
    static constexpr int SIZE_Y = 16;
    static constexpr int SIZE_Z = 16;

    Chunk(glm::vec3 position);

    void generateTestData();       // fills the chunk with blocks (for debugging)
    void buildMesh();              // builds mesh from blocks
    void draw() const;             // draws the chunk's mesh
    glm::vec3 getPosition() const { return position; }

private:
    glm::vec3 position;
    Mesh mesh;
    uint8_t blocks[SIZE_X][SIZE_Y][SIZE_Z];

    void addFace(std::vector<float>& vertices,
        std::vector<unsigned int>& indices,
        int x, int y, int z,
        const glm::vec3 faceVerts[4]);

};