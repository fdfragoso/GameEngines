//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include "MovingPlatformComponent.hpp"
#include "PlatformComponent.hpp"
#include "GameObject.hpp"

MovingPlatformComponent::MovingPlatformComponent(GameObject *gameObject) : Component(gameObject)
{
    platformComponent = gameObject->getComponent<PlatformComponent>();
}

void MovingPlatformComponent::update(float deltaTime) {
    totalTime += deltaTime;
	
	float interval = fmod(totalTime, 6);
    // todo replace with easing function
    if (interval>3){
		
		float t = (interval - 3)/3.0f;
		t = glm::smoothstep(0.0f, 1.0f, t);
		auto pos = glm::mix(movementStart, movementEnd, t);
        platformComponent->moveTo(pos);
    } else {
		float t = interval/ 3.0f;
		t = glm::smoothstep(0.0f, 1.0f, t);
		auto pos = glm::mix(movementEnd, movementStart, t);
        platformComponent->moveTo(pos);
    }
}

void MovingPlatformComponent::setMovementStart(glm::vec2 pos) {
    movementStart = pos;
}

void MovingPlatformComponent::setMovementEnd(glm::vec2 pos) {
    movementEnd = pos;
}
