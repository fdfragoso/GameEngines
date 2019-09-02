
#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"
#include "SDL_mixer.h"

void BirdController::update(float deltaTime)
{
	physicsComp->setLinearVelocity(glm::vec2(1.0f, physicsComp->getLinearVelocity().y));
}

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
	physicsComp = gameObject->getComponent<PhysicsComponent>();
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
		physicsComp->addImpulse(glm::vec2(0, 0.15f));
    } else if (event.type == SDL_KEYUP){
    }
    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
	std::string objName = comp->getGameObject()->name;
	if (objName == "Wall top" || objName == "Wall bottom") 
	{
		BirdGame::instance->setGameState(GameState::GameOver);
	}
	else if (objName == "Coin") 
	{
		comp->getGameObject()->name = "Cow";
		comp->getGameObject()->removeComponent(comp->getGameObject()->getComponent<SpriteComponent>());
		BirdGame::instance->coinCollected();
	}
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


