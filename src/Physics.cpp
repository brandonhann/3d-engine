#include "Physics.h"
#include "player/Player.h"
#include "terrain/Chunk.h"

Physics::Physics(Player& player, Chunk& chunk)
    : player(player), chunk(chunk), gravity(-9.8f) {}

void Physics::update(float deltaTime) {
    // Apply gravity
    player.position.y += gravity * deltaTime;

    // Collision detection
    float terrainHeight = chunk.getHeight(player.position.x, player.position.z);
    if (player.position.y < terrainHeight) {
        player.position.y = terrainHeight; // Prevent player from going into the terrain
    }
}
