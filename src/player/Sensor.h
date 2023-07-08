#ifndef SENSOR_H
#define SENSOR_H

#include "Player.h"
#include "../terrain/Chunk.h"
#include <iostream>

class Sensor {
public:
    Sensor(Player& player, Chunk& chunk)
        : player(player), chunk(chunk) {}

    void update() {
        if (checkCollision()) {
            std::cout << "Touched" << std::endl;
        }
    }

    bool checkCollision() {
        // Get the min and max points for each bounding box
        glm::vec3 playerMin = player.getMin();
        glm::vec3 playerMax = player.getMax();
        glm::vec3 chunkMin = chunk.getMin();
        glm::vec3 chunkMax = chunk.getMax();

        // Check for intersection on all three axes
        if (playerMax.x < chunkMin.x || playerMin.x > chunkMax.x ||
            playerMax.y < chunkMin.y || playerMin.y > chunkMax.y ||
            playerMax.z < chunkMin.z || playerMin.z > chunkMax.z) {
            return false;
        }

        return true;
    }

private:
    Player& player;
    Chunk& chunk;
};

#endif