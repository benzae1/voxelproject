#include "world.hpp"
#include "block.hpp"

World::World(int worldWidth, int worldDepth)
    : width(worldWidth), depth(worldDepth) {
    // Create chunk grid
    for (int cx = 0; cx < width; cx++)
        for (int cz = 0; cz < depth; cz++) {
            glm::vec3 chunkPos(
                cx * Chunk::SIZE_X,
                0,
                cz * Chunk::SIZE_Z
            );
            chunks.push_back(new Chunk(chunkPos));
        }
}

int World::getHeight(int x, int z) {
    // simple noise-like height
    float h =
        (std::sin(x * 0.1f) + std::cos(z * 0.1f)) * 5.0f +
        (std::sin(x * 0.05f + z * 0.08f) * 3.0f);

    return (int)std::round(h + 20.0f);   // offset so terrain is above 0
}

void World::generateTerrain() {
    for (auto* chunk : chunks) {
        for (int x = 0; x < Chunk::SIZE_X; x++)
            for (int z = 0; z < Chunk::SIZE_Z; z++) {

                int worldX = (int)chunk->getPosition().x + x;
                int worldZ = (int)chunk->getPosition().z + z;

                int h = getHeight(worldX, worldZ);

                // Smooth, constant thickness
                const int dirtLayers = 4;

                for (int y = 0; y < Chunk::SIZE_Y; y++) {

                    int worldY = y + (int)chunk->getPosition().y;

                    if (worldY > h) {
                        chunk->blocks[x][y][z] = BLOCK_AIR;
                    }
                    else if (worldY == h) {
                        chunk->blocks[x][y][z] = BLOCK_GRASS;
                    }
                    else if (worldY >= h - dirtLayers) {
                        chunk->blocks[x][y][z] = BLOCK_DIRT;
                    }
                    else {
                        chunk->blocks[x][y][z] = BLOCK_STONE;
                    }
                }
            }
    }

    for (auto* chunk : chunks)
        chunk->buildMesh();
}

void World::draw() {
    for (auto* c : chunks)
        c->draw();
}