#include "SnakeGUI.hpp"
#include "SnakeBody.hpp"
#include <iostream>
#include <ctime>
#undef main

SnakeGUI::SnakeGUI() {
    r.setWindowSize({1200,800});
    r.init(SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL);

    time_t t;                                               // random seed based on time
    srand((unsigned) time(&t));

    atlas = SpriteAtlas::create("snake.json","snake.png");

    int width = 12;
    int height = 8;
    setupLevel(width, height);
    restart();

    camera.setWindowCoordinates();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };
    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}

void SnakeGUI::restart(){
    snake.init(4,10,10, 1,0);
    placeFood();
    tickRate = 0.25f;
    playing = true;
    score = 0;
}

void SnakeGUI::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {.3, .3, 1, 1})
            .build();

    renderPass.draw(levelSprites);              // render level

    // render snake
    auto sb = SpriteBatch::create();
    auto body = snake.snakeHead;
    auto sprite = atlas->get("snake-body.png");
    while (body != nullptr){
        sprite.setPosition({(body->x+0.5f)*snakeBlockSize, (body->y+0.5f)*snakeBlockSize});
        glm::vec4 green{.5f,1,.5f,1};
        glm::vec4 red{1,.5f,.5f,1};
        sprite.setColor(playing?green:red);
        sb.addSprite(sprite);
        body = body->next;
    }
    auto berry = atlas->get("berry.png");
    berry.setPosition({(foodX+0.5f)*snakeBlockSize, (foodY+0.5f)*snakeBlockSize});
    sb.addSprite(berry);
    auto snakeSprites = sb.build();
    renderPass.draw(snakeSprites);

    float winWidth = 250;
    ImGui::SetNextWindowPos(ImVec2((Renderer::instance->getWindowSize().x - winWidth)*0.5f, .0f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(winWidth, 70), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize);
    ImGui::LabelText("Score", "%i",score);
    ImGui::LabelText("SnakeBody#", "%i",SnakeBody::totalSnakeBodies);
    ImGui::End();
}

void SnakeGUI::keyEvent(SDL_Event &keyEvent) {
    if (keyEvent.type == SDL_KEYDOWN){
        if (playing){
            switch (keyEvent.key.keysym.sym){
                case SDLK_DOWN:
                    snake.setMoveDirection(0,-1);
                    break;
                case SDLK_UP:
                    snake.setMoveDirection(0,1);
                    break;
                case SDLK_LEFT:
                    snake.setMoveDirection(-1,0);
                    break;
                case SDLK_RIGHT:
                    snake.setMoveDirection(1,0);
                    break;
            }
        } else {
            restart();
        }
    }
}

void SnakeGUI::update(float deltaTime) {
    static float tickTime = 0;
    tickTime+=deltaTime;

    if (tickTime>tickRate && playing){
        tickTime = (float)fmod(tickTime,tickRate);

        int nextPosX = snake.moveX + snake.snakeHead->x;
        int nextPosY = snake.moveY + snake.snakeHead->y;

        if (level.snakeCollide(nextPosX, nextPosY)){
            playing = false;
        } else if (snake.collide(nextPosX, nextPosY)){
            playing = false;
        } else {
            if (nextPosX == foodX && nextPosY == foodY){
                score++;
                snake.grow();
                placeFood();
                tickRate = tickRate*0.95f;
            }
            snake.move();
        }
    }
}

void SnakeGUI::setupLevel(int width, int height) {
    level.init(width, height);

    auto sb = SpriteBatch::create();
    for (int x=0;x<width;x++){
        for (int y=0;y<height;y++) {
            std::string spriteName = level.isBlocked(x,y)?"brick.png":"background.png";
            auto sprite = atlas->get(spriteName);
            sprite.setPosition({(x+0.5f)*levelBlockSize,(y+0.5f)*levelBlockSize});
            sb.addSprite(sprite);
        }
    }
    levelSprites = sb.build();

}

void SnakeGUI::placeFood() {
    int blocksPerLevelBlock = 100/25;

    foodX = (rand()%(level.width-2) + 1)*blocksPerLevelBlock;
    foodY = (rand()%(level.height-2) + 1)*blocksPerLevelBlock;
}

int main(){
    new SnakeGUI();
    return 0;
}