#include <glm/gtx/rotate_vector.hpp>
#include "FirstPersonController.hpp"
#include "SDL_mouse.h"
#include "sre\Camera.hpp"

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera * camera)
:camera(camera)
{
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	fwd = false;
	bwd = false;
	right = false;
	left = false;
    camera->setPerspectiveProjection(45,0.1f,1000);
    position = vec3(0,0,0);
}


void FirstPersonController::update(float deltaTime){
    
	if (fwd) 
	{
		position += glm::rotateY(vec3(0, 0, -1), glm::radians(rotation)) * deltaTime * moveSpeed;
	}
	else if (bwd) 
	{
		position += glm::rotateY(vec3(0, 0, 1), glm::radians(rotation)) * deltaTime * moveSpeed;
	}

	if (right)
	{
		position += glm::rotateY(vec3(1, 0, 0), glm::radians(rotation)) * deltaTime * moveSpeed;
	}
	else if (left)
	{
		position += glm::rotateY(vec3(-1, 0, 0), glm::radians(rotation)) * deltaTime * moveSpeed;
	}

	glm::mat4 translationM = glm::translate(position);
	glm::mat4 rotationM = glm::rotate(glm::radians(rotation), glm::vec3(0,1,0));
	camera->setViewTransform(inverse(translationM*rotationM));

    //camera->lookAt(vec3(0,0,0), vec3(0,0,-1), vec3{0,1,0});
}

void FirstPersonController::onKey(SDL_Event &keyEvent) {
	
	if (keyEvent.key.keysym.sym == SDLK_w) 
	{
		if (keyEvent.type == SDL_KEYDOWN) 
		{
			fwd = true;
		}
		else if (keyEvent.type == SDL_KEYUP)
		{
			fwd = false;
		}
	}

	if (keyEvent.key.keysym.sym == SDLK_a) 
	{
		if (keyEvent.type == SDL_KEYDOWN)
		{
			left = true;
		}
		else if (keyEvent.type == SDL_KEYUP)
		{
			left = false;
		}
	}

	if (keyEvent.key.keysym.sym == SDLK_s) 
	{
		if (keyEvent.type == SDL_KEYDOWN)
		{
			bwd = true;
		}
		else if (keyEvent.type == SDL_KEYUP)
		{
			bwd = false;
		}
	}

	if (keyEvent.key.keysym.sym == SDLK_d)
	{
		if (keyEvent.type == SDL_KEYDOWN)
		{
			right = true;
		}
		else if (keyEvent.type == SDL_KEYUP)
		{
			right = false;
		}
	}
}

void FirstPersonController::onMouse(SDL_Event &mouseEvent) {
	
	if (mouseEvent.type == SDL_MOUSEMOTION) 
	{
		rotation -= mouseEvent.motion.xrel * 0.25f;
	}
    
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    
	this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
