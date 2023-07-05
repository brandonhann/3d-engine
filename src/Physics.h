#ifndef PHYSICS_H
#define PHYSICS_H

#include "player/Player.h"
#include "terrain/Chunk.h"

class Physics {
public:
    Physics(Player& player, Chunk& chunk);

    // Updates physics state
    void update(float deltaTime);

private:
    Player& player;
    Chunk& chunk;

    float gravity;
};

#endif