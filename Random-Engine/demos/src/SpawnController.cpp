//Needed header
#include "SpawnController.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"
#include "SceneManager.hpp"

#include <iostream>

using namespace SRE;

SpawnController::SpawnController(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void SpawnController::Start() {
	haveToReset = false;
	auto pos = gameObject->getComponent<TransformCmp>()->getGlobalPosition();
	spawn();
}

void SpawnController::Update(float dt) {
	if (haveToReset) {
		spawn();
	}
}

void SpawnController::OnCollisionEnter(GameObject * other) {
	auto name = other->getName();
	if (name == "parallaxC" || name == "parallaxCRight") {
		haveToReset = true;
	}
}

void SpawnController::spawn() {
	auto movVel = RandomInterpolation::interpolate({minVel,0,0,0}, {maxVel,0,0,0}, 0, InterpolationType::Random);
	gameObject->getComponent<TransformCmp>()->setPosition(initPos);
	gameObject->getComponent<TransformCmp>()->setRotation({0,0,0});
	gameObject->getComponent<Body2DCmp>()->myBody->SetLinearVelocity({ movVel.x,0});
	gameObject->getComponent<Body2DCmp>()->myBody->SetAngularVelocity(0);
	haveToReset = false;
}

void SpawnController::setVel(float newMinVel, float newMaxVel) {
	minVel = newMinVel;
	maxVel = newMaxVel;
}