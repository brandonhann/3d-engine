#ifndef CHUNK_H
#define CHUNK_H

#include "Terrain.h"
#include <glm/glm.hpp>

class Chunk {
public:
    Chunk(Terrain& terrain, glm::vec2 position);
    void drawChunk();

private:
    Terrain& terrain;
    glm::vec2 position;
};

#endif