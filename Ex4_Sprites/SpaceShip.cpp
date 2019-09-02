
#include <glm/gtx/rotate_vector.hpp>
#include "SpaceShip.hpp"
#include "sre/Renderer.hpp"
#include "AsteroidsGame.hpp"
#include "LaserShot.h"
#include <string>
#include <iostream>

SpaceShip::SpaceShip(const sre::Sprite &sprite, AsteroidsGame* _gameManager) : GameObject(sprite) {
	_myType = SpaceShipCol;
	gameManager = _gameManager;
    scale = glm::vec2(0.5f,0.5f);
    winSize = sre::Renderer::instance->getWindowSize();
    radius = 23;
    position = winSize * 0.5f;
}

void SpaceShip::update(float deltaTime) {
	coolDownTimer -= deltaTime;
    if (thrust){
        float acceleration = deltaTime*thrustPower;
        glm::vec2 direction = glm::rotateZ(glm::vec3(0,acceleration,0), glm::radians(rotation));
        velocity += direction;
        float speed = glm::length(velocity);
        if (speed > maxSpeed){
            velocity = velocity * (maxSpeed / speed);
        }
    } else {
        velocity = velocity * (1.0f - drag*deltaTime);
    }
    position += velocity * deltaTime;
    if (rotateCCW){
        rotation += deltaTime * rotationSpeed;
    }
    if (rotateCW){
        rotation -= deltaTime * rotationSpeed;
    }

    if (position.x < 0){
        position.x += winSize.x;
    } else if (position.x > winSize.x){
        position.x -= winSize.x;
    }
    if (position.y < 0){
        position.y += winSize.y;
    } else if (position.y > winSize.y){
        position.y -= winSize.y;
    }
}

void SpaceShip::onCollision(std::shared_ptr<GameObject> other, CollidableType colType)
{
	if (colType == AsteroidCol)
	{
		gameManager->SpawnBang(position);
		gameManager->DeleteObject(this);
	}
}

void SpaceShip::onKey(SDL_Event &keyEvent) {
    if (keyEvent.key.keysym.sym == SDLK_UP){
        thrust = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_LEFT){
        rotateCCW = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_RIGHT){
        rotateCW = keyEvent.type == SDL_KEYDOWN;
    }
	if (keyEvent.key.keysym.sym == SDLK_SPACE) 
	{
		if (keyEvent.type == SDL_KEYDOWN) 
		{
			if (coolDownTimer <= 0)
			{
				fireLaser();
			}
		}
	}
}

void SpaceShip::fireLaser() 
{
	coolDownTimer = shootCooldown;
	glm::vec2 up = glm::vec2(0,1);
	
	glm::vec2 dir = glm::rotate(up, glm::radians(rotation));
	//glm::rota
	gameManager->SpawnLaser(position, rotation ,dir);
}
