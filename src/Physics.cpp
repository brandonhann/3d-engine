#include "Physics.h"
#include "player/Player.h"
#include "terrain/Chunk.h"
#include "player/Sensor.h"

Physics::Physics(Player& player, Chunk& chunk)
    : player(player), chunk(chunk), gravity(-9.8f) {}

void Physics::update(float deltaTime) {
    // Collision detection
    Sensor sensor(player, chunk);
    float terrainHeight = chunk.getHeight(player.position.x, player.position.z);

    // Apply gravity if the player is not above a terrain chunk
    if (!sensor.checkCollision() || player.position.y > terrainHeight) {
        player.position.y += gravity * deltaTime;
    }
    else if (player.position.y < terrainHeight) {
        player.position.y = terrainHeight; // Prevent player from going into the terrain
    }
}


