#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"

class SpaceShip : public GameObject, public Collidable  {
public:
    SpaceShip(const sre::Sprite &sprite, AsteroidsGame* _gameManager);

    void update(float deltaTime) override;

    void onCollision(std::shared_ptr<GameObject> other, CollidableType colType) override;

    void onKey(SDL_Event &keyEvent) override;

	void fireLaser();

    glm::vec2 velocity;

private:
	AsteroidsGame* gameManager;
    bool rotateCW = false;
    bool rotateCCW = false;
    bool thrust = false;
	float coolDownTimer = 0;
    float drag = 0.80f;
    float maxSpeed = 200.0f;
    float thrustPower = 300.0f;
    float rotationSpeed = 100.0f;
	const float shootCooldown = 0.5f;
    glm::vec2 winSize;
};


