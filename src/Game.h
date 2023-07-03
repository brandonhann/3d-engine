#pragma once
#include "Window.h"
#include "shaders/Shader.h"
#include "player/Player.h"
#include "player/Camera.h"
#include "player/InputManager.h"
#include "terrain/Terrain.h"
#include "terrain/Chunk.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    Window window;
    Shader shader;
    Player player;
    Camera camera;
    InputManager inputManager;
    Terrain terrain;
    Chunk chunk;
};

int main() {
    Game game;
    game.run();
    return 0;
}
