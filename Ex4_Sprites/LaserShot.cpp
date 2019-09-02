#include "LaserShot.h"
#include "AsteroidsGame.hpp"
#include "SpaceShip.hpp"
#include <string>
#include <iostream>

LaserShot::LaserShot(const sre::Sprite & sprite, glm::vec2 _spawnLocation, glm::vec2 _velocity, float _rotation, AsteroidsGame* _gameManager) : GameObject(sprite)
{
	_myType = LaserCol;
	winSize = sre::Renderer::instance->getWindowSize();
	gameManager = _gameManager;
	speed = 500.0f;
	lifetime = 1.0f;
	position = _spawnLocation;
	velocity = _velocity;
	rotation = _rotation;
	//radius = 6.0f;
}

void LaserShot::onCollision(std::shared_ptr<GameObject> other, CollidableType colType)
{
	/*SpaceShip * test1 = dynamic_cast<SpaceShip*>(other.get());
	if (test1 != NULL)
	{
		return;
	}
	LaserShot * test2 = dynamic_cast<LaserShot*>(other.get());
	if (test2 != NULL)
	{
		return;
	}*/
	if(colType==AsteroidCol)
	{
		gameManager->DeleteObject(this);
	}
	
}


void LaserShot::update(float deltaTime)
{
	lifetime -= deltaTime;
	if (lifetime <= 0) 
	{
		gameManager->DeleteObject(this);
	}
	position += velocity * speed * deltaTime;
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
}

