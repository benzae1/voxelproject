#pragma once

#include <vector>
#include <unordered_map>
#include "chunk.hpp"

class World {
public:
    World(int worldWidth, int worldDepth);

    void generateTerrain();
    void draw();

private:
    int width;      // number of chunks in X direction
    int depth;      // number of chunks in Z direction

    std::vector<Chunk*> chunks;

    int getHeight(int x, int z);
};