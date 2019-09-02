#pragma once

#include "BirdGame.hpp"
#include "Component.hpp"
#include "SDL_mixer.h"

class BirdController : public Component {
private:
	std::shared_ptr<PhysicsComponent> physicsComp;

	void update(float deltaTime) override;

	Mix_Chunk* coinSound;
	
public:
    explicit BirdController(GameObject *gameObject);

    bool onKey(SDL_Event &event) override;

    void onCollisionStart(PhysicsComponent *comp) override;

    void onCollisionEnd(PhysicsComponent *comp) override;
};
