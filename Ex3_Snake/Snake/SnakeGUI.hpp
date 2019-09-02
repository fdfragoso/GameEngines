#pragma once

#include "SDL.h"
#include <sre/SpriteAtlas.hpp>
#include <sre/SDLRenderer.hpp>
#include "Level.hpp"
#include "Snake.hpp"

using namespace sre;


class SnakeGUI {
public:
    SnakeGUI();
private:
    void setupLevel(int width, int height);
    void update(float deltaTime);
    void keyEvent(SDL_Event &mouseEvent);
    void render();
    void placeFood();
    void restart();
    std::shared_ptr<SpriteAtlas> atlas;
    SDLRenderer r;
    Camera camera;
    Level level;
    Snake snake;
    int foodX;
    int foodY;
    int score;
    bool playing = true;
    float tickRate = 0.25f;
    const int levelBlockSize = 100;
    const int snakeBlockSize = 25;
    std::shared_ptr<sre::SpriteBatch> levelSprites;
};
