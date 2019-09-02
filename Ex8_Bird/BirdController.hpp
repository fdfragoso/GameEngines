#pragma once

#include "Component.hpp"

class BirdController : public Component {
private:
	std::shared_ptr<PhysicsComponent> physicsComp;

	void update(float deltaTime) override;
	
public:
    explicit BirdController(GameObject *gameObject);

    bool onKey(SDL_Event &event) override;

    void onCollisionStart(PhysicsComponent *comp) override;

    void onCollisionEnd(PhysicsComponent *comp) override;
};
