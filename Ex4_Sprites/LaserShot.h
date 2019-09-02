#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"

class LaserShot : public GameObject, public Collidable {
public:
	LaserShot(const sre::Sprite &sprite, glm::vec2 _spawnLocation, glm::vec2 _velocity, float _rotation, AsteroidsGame* _gameManager);
	void onCollision(std::shared_ptr<GameObject> other, CollidableType colType) override;
	void update(float deltaTime) override;
private:
	glm::vec2 velocity;
	glm::vec2 winSize;
	AsteroidsGame* gameManager;
	float speed;
	float lifetime;
	bool rotateCW = false;
};