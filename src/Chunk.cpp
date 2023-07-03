#include "Chunk.h"

Chunk::Chunk(Terrain& terrain, glm::vec2 position)
    : terrain(terrain), position(position) {}

void Chunk::drawChunk() {
    terrain.drawTerrain();
}