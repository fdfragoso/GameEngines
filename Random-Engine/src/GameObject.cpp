#include <iostream>
#include "GameObject.hpp"
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include <glm/gtc/random.hpp>

//Random Engine
#include "RandomEngine.hpp"

using namespace SRE;

GameObject::GameObject(std::string name_)
:name(name_)
{
}

GameObject::~GameObject() {
}


std::string GameObject::getName() {
    return name;
}


bool GameObject::removeComponent(std::shared_ptr<Component> ptr) {
    for (auto iter = components.begin();iter != components.end(); iter++){
        if (*iter == ptr){
            components.erase(iter);
            ptr.reset();
            return true;
        }
    }
    return false;
}

void GameObject::draw() {
	if (!visible) {
		return;
	}
	auto transformCmp = this->getComponent<TransformCmp>();
	auto meshCmp = this->getComponent<MeshCmp>();
	auto particleCmp = this->getComponent<ParticleEmitterCmp>();
	auto spriteCmp = this->getComponent<SpriteRendererCmp>();
	auto animationCmp = this->getComponent<AnimationCmp>();

	if (meshCmp != nullptr && transformCmp != nullptr) {
		meshCmp->render(transformCmp->globalTransform());
	}

	if (spriteCmp != nullptr && transformCmp != nullptr) {
		if (animationCmp != nullptr) {
			spriteCmp->sprite = animationCmp->getCurrentSprite();
		}
		spriteCmp->render(transformCmp->globalTransform());
	}

	if (particleCmp != nullptr && transformCmp != nullptr) {
		glm::vec3 velocity = particleCmp->getVelocity();
		glm::vec3 position = transformCmp->getGlobalPosition();
		particleCmp->emit(position, velocity);
		particleCmp->update();
		particleCmp->render();
	}
}

void GameObject::updateCollider() {
	auto transformCmp = this->getComponent<TransformCmp>();
	auto bodyCmp = this->getComponent<Body2DCmp>();

	if (bodyCmp != nullptr && transformCmp != nullptr) {
		auto myBody = bodyCmp->myBody;
		/*if (myBody->GetType() == b2_staticBody) {
		}*/
		glm::vec3 tPos = transformCmp->getGlobalPosition();
		glm::vec3 tRot = transformCmp->getGlobalRotation();
		auto bPos = myBody->GetPosition();
		float tR = tRot.z;
		float bR = myBody->GetAngle() * RAD_TO_DEG;
		if (tPos.x != bPos.x || tPos.y != bPos.y || tR != bR) {
			myBody->SetTransform({ tPos.x, tPos.y }, tR * DEG_TO_RAD);
		}
	}
}
void GameObject::updateGlobalTransform() {
	auto transformCmp = this->getComponent<TransformCmp>();
	auto bodyCmp = this->getComponent<Body2DCmp>();

	if (bodyCmp != nullptr && transformCmp != nullptr) {
		auto myBody = bodyCmp->myBody;
		if (myBody->GetType() != b2_staticBody) {
			glm::vec3 parentP = transformCmp->getGlobalPosition() - transformCmp->position;
			glm::vec3 parentR = transformCmp->getGlobalRotation() - transformCmp->rotation;
			transformCmp->setPosition({ myBody->GetPosition().x - parentP.x, myBody->GetPosition().y - parentP.y, 0 });
			transformCmp->setRotation({ 0, 0, myBody->GetAngle()*RAD_TO_DEG - parentR.z});
		}
	}
}

void GameObject::scriptUpdate(float dt) {
	auto scriptableCmp = this->getComponent<ScriptableCmp>();

	if (scriptableCmp != nullptr) {
		scriptableCmp->Update(dt);
	}
}

void GameObject::scriptStart() {
	auto scriptableCmp = this->getComponent<ScriptableCmp>();

	if (scriptableCmp != nullptr ) {
		scriptableCmp->Start();
	}
}

void GameObject::showGUI() {
	auto scriptableCmp = this->getComponent<ScriptableCmp>();

	if (scriptableCmp != nullptr) {
		scriptableCmp->OnGUI();
	}
}