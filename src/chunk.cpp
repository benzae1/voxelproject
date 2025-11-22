#include "chunk.hpp"

Chunk::Chunk(glm::vec3 pos)
    : position(pos)
{
    // initialize all blocks to 0 (air)
    memset(blocks, 0, sizeof(blocks));
}

void Chunk::generateTestData()
{
    // simple test: fill bottom half with blocks
    for (int x = 0; x < SIZE_X; x++)
        for (int y = 0; y < SIZE_Y / 2; y++)
            for (int z = 0; z < SIZE_Z; z++)
                blocks[x][y][z] = 1;   // solid block
}

// face definitions
static const glm::vec3 faceOffsets[6][4] = {
    // Back
    { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0} },
    // Front
    { {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} },
    // Left
    { {0,0,0}, {0,0,1}, {0,1,1}, {0,1,0} },
    // Right
    { {1,0,0}, {1,0,1}, {1,1,1}, {1,1,0} },
    // Bottom
    { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1} },
    // Top
    { {0,1,0}, {1,1,0}, {1,1,1}, {0,1,1} }
};

void Chunk::addFace(std::vector<float>& vertices,
    std::vector<unsigned int>& indices,
    int x, int y, int z,
    const glm::vec3 faceVerts[4]) {
    unsigned int startIndex = vertices.size() / 8;

    for (int i = 0; i < 4; i++) {
        glm::vec3 p = faceVerts[i] + glm::vec3(x, y, z) + position;

        vertices.insert(vertices.end(), {
            p.x, p.y, p.z,             // pos
            1.0f, 1.0f, 1.0f,           // color (white for now)
            (float)(i == 1 || i == 2), // u
            (float)(i >= 2)            // v
            });
    }

    indices.insert(indices.end(), {
        startIndex, startIndex + 1, startIndex + 2,
        startIndex, startIndex + 2, startIndex + 3
        });
}

void Chunk::buildMesh()
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    auto isSolid = [&](int x, int y, int z) {
        if (x < 0 || x >= SIZE_X ||
            y < 0 || y >= SIZE_Y ||
            z < 0 || z >= SIZE_Z)
            return false;
        return blocks[x][y][z] != 0;
        };

    for (int x = 0; x < SIZE_X; x++)
        for (int y = 0; y < SIZE_Y; y++)
            for (int z = 0; z < SIZE_Z; z++)
            {
                if (!blocks[x][y][z]) continue;

                if (!isSolid(x, y, z - 1)) addFace(vertices, indices, x, y, z, faceOffsets[0]);
                if (!isSolid(x, y, z + 1)) addFace(vertices, indices, x, y, z, faceOffsets[1]);
                if (!isSolid(x - 1, y, z)) addFace(vertices, indices, x, y, z, faceOffsets[2]);
                if (!isSolid(x + 1, y, z)) addFace(vertices, indices, x, y, z, faceOffsets[3]);
                if (!isSolid(x, y - 1, z)) addFace(vertices, indices, x, y, z, faceOffsets[4]);
                if (!isSolid(x, y + 1, z)) addFace(vertices, indices, x, y, z, faceOffsets[5]);
            }

    mesh.update(vertices, indices);
}

void Chunk::draw() const
{
    mesh.draw();
}
