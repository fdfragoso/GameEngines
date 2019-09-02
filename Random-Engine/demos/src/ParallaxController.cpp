//Needed header
#include "ParallaxController.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"
#include "SceneManager.hpp"

#include <iostream>

using namespace SRE;

ParallaxController::ParallaxController(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void ParallaxController::Start() {
	maxVel = -200;
	haveToReset = false;
	auto pos = gameObject->getComponent<TransformCmp>()->getGlobalPosition();
	initPos = glm::vec3(35, pos.y, 0);
}

void ParallaxController::Update(float dt) {
	movVel *= 1.0005;
	if (movVel< maxVel) {
		movVel = maxVel;
	}
	gameObject->getComponent<Body2DCmp>()->myBody->SetLinearVelocity({ movVel, 0 });
	if (haveToReset) {
		gameObject->getComponent<TransformCmp>()->setPosition(initPos);
		gameObject->getComponent<Body2DCmp>()->myBody->SetLinearVelocity({ movVel, 0 });
		haveToReset = false;
	}
}


void ParallaxController::OnCollisionEnter(GameObject * other) {
	if (other->getName() == "parallaxC") {
		haveToReset = true;
	}
}
