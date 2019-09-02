#include "RandomPhysics2D.hpp"
#include "SRE/Debug.hpp"
#include "GameObject.hpp"
#include "RandomEngine.hpp"

#include <iostream>

b2World* RandomPhysics2D::world = nullptr;

void RandomPhysics2D::startRandomPhysics2D() {
	RandomPhysics2D::world = new b2World(b2Vec2(0, -9.89f));
	debugDrawInstance = new DebugDraw();
	world->SetContactListener(this);
	world->SetDebugDraw(debugDrawInstance);
	debugDrawInstance->SetFlags(DebugDraw::e_shapeBit);
}

void RandomPhysics2D::stopRandomPhysics2D() {
	delete debugDrawInstance;
	delete RandomPhysics2D::world;
	RandomPhysics2D::world = nullptr;
}

void RandomPhysics2D::BeginContact(b2Contact* contact) {
	if (RandomEngine::pauseEngine) {
		return;
	}
	auto fa = (GameObject*)contact->GetFixtureA()->GetUserData();
	auto faScript = fa->getComponent<ScriptableCmp>();
	auto fb = (GameObject*)contact->GetFixtureB()->GetUserData();
	auto fbScript = fb->getComponent<ScriptableCmp>();
	if (faScript != nullptr) {
		faScript->OnCollisionEnter(fb);
	}
	if (fbScript != nullptr) {
		fbScript->OnCollisionEnter(fa);
	}
}

void RandomPhysics2D::EndContact(b2Contact* contact) {
	if (RandomEngine::pauseEngine) {
		return;
	}
	auto fa = (GameObject*)contact->GetFixtureA()->GetUserData();
	auto faScript = fa->getComponent<ScriptableCmp>();
	auto fb = (GameObject*)contact->GetFixtureB()->GetUserData();
	auto fbScript = fb->getComponent<ScriptableCmp>();
	if (faScript != nullptr) {
		faScript->OnCollisionExit(fb);
	}
	if (fbScript != nullptr) {
		fbScript->OnCollisionExit(fa);
	}
}