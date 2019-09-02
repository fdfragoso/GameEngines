#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "AsteroidsGame.hpp"

class Asteroid : public GameObject, public Collidable {
public:
	Asteroid(const sre::Sprite &sprite, float _colliderSize, AsteroidsGame* _gameManager, AsteroidSize _mySize);
	Asteroid(const sre::Sprite &sprite, float _colliderSize, glm::vec2 _spawnPos , AsteroidsGame* _gameManager, AsteroidSize _mySize);
	void onCollision(std::shared_ptr<GameObject> other, CollidableType colType) override;
	void update(float deltaTime) override;

private:
	glm::vec2 randomScreenPosition();
	glm::vec2 randomVelocity();
	float randomSpeed();
	
	AsteroidSize mySize;
	glm::vec2 winSize;
	glm::vec2 velocity;
	AsteroidsGame* gameManager;
	float speed;
	float rotationSpeed;
	bool rotateCW = false;
};