#include <glm/gtx/rotate_vector.hpp>

#include "Asteroid.h"
#include "sre/Renderer.hpp"
#include "AsteroidsGame.hpp"
#include <string>
#include <iostream>

Asteroid::Asteroid(const sre::Sprite & sprite, float _colliderSize, AsteroidsGame* _gameManager, AsteroidSize _mySize) : GameObject(sprite)
{
	_myType = AsteroidCol;
	mySize = _mySize;
	gameManager = _gameManager;
	winSize = sre::Renderer::instance->getWindowSize();
	scale = glm::vec2(1, 1);
	radius = _colliderSize;
	position = randomScreenPosition();
	velocity = randomVelocity();
	speed = randomSpeed();
	rotationSpeed = randomSpeed();
	int output = (rand() % static_cast<int>(2));
	if (output == 0) 
	{
		rotateCW = true;
	}
}

Asteroid::Asteroid(const sre::Sprite & sprite, float _colliderSize, glm::vec2 _spawnPos, AsteroidsGame * _gameManager, AsteroidSize _mySize) : GameObject(sprite)
{
	_myType = AsteroidCol;
	mySize = _mySize;
	gameManager = _gameManager;
	winSize = sre::Renderer::instance->getWindowSize();
	scale = glm::vec2(1, 1);
	radius = _colliderSize;
	position = _spawnPos;
	velocity = randomVelocity();
	speed = randomSpeed();
	rotationSpeed = randomSpeed();
	int output = (rand() % static_cast<int>(2));
	if (output == 0)
	{
		rotateCW = true;
	}
}

void Asteroid::onCollision(std::shared_ptr<GameObject> other, CollidableType _otherType)
{
	if(_otherType == SpaceShipCol || _otherType == LaserCol)
	{
		gameManager->SpawnAsteroid(mySize, position);
		gameManager->IncreaseScore();
		gameManager->DeleteObject(this);
	}
}

void Asteroid::update(float deltaTime)
{
	position += velocity * speed * deltaTime;
	// wrap around
	if (position.x < 0) {
		position.x += winSize.x;
	}
	else if (position.x > winSize.x) {
		position.x -= winSize.x;
	}
	if (position.y < 0) {
		position.y += winSize.y;
	}
	else if (position.y > winSize.y) {
		position.y -= winSize.y;
	}

	if (rotateCW) {
		rotation -= deltaTime * rotationSpeed;
	}
	else 
	{
		rotation += deltaTime * rotationSpeed;
	}
}

glm::vec2 Asteroid::randomScreenPosition()
{
	glm::vec2 randScreenPos;
	float randY;
	float randX;
	do {
		randX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / winSize.x));
		randY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / winSize.y));
	} while (((randX > (winSize.x * 0.2f)) && (randX < (winSize.x * 0.8f))) && ((randY > (winSize.y * 0.2f)) && (randY < (winSize.y * 0.8f))));
	randScreenPos.x = randX;
	randScreenPos.y = randY;
	return randScreenPos;
}

glm::vec2 Asteroid::randomVelocity()
{
	glm::vec2 randVelocity;
	float _x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float _y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	randVelocity.x = _x;
	randVelocity.y = _y;
	randVelocity = glm::normalize(randVelocity);
	return randVelocity;
}

float Asteroid::randomSpeed() 
{
	return 10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (100 - 10)));
}

