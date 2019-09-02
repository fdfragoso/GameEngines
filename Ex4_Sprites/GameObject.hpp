#pragma once

#include <SDL_events.h>
#include "sre/Sprite.hpp"
#include "sre/SpriteBatch.hpp"

class GameObject {
public:
    explicit GameObject(sre::Sprite sprite);
    virtual ~GameObject();
    virtual void render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
    virtual void update(float deltaTime);
    virtual void onKey(SDL_Event& keyEvent);
protected:
    glm::vec2 position;
    glm::vec2 scale;
    sre::Sprite sprite;
    float rotation;

    friend class AsteroidsGame;
};
