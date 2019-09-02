
#include <iostream>

#include "Body2DCmp.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.hpp"
#include "RandomEngine.hpp"

using namespace SRE;

Body2DCmp::Body2DCmp(GameObject *gameObject)
	:Component(gameObject) {

}

void Body2DCmp::setUp(RandomShape2DType shapeType, b2BodyType bodyType) {
	b2BodyDef myBd;
	b2FixtureDef fd;
	myBody = RandomPhysics2D::world->CreateBody(&myBd);
	glm::vec3 scale = gameObject->getComponent<TransformCmp>()->scale;
	glm::vec3 position = gameObject->getComponent<TransformCmp>()->getGlobalPosition();
	glm::vec3 rotation = gameObject->getComponent<TransformCmp>()->getGlobalRotation();
	float rZ = rotation.z;
	if (shapeType == RandomShape2DType::Box) {
		b2PolygonShape shape;
		shape.SetAsBox(scale.x, scale.y, b2Vec2(0.0f, 0.0f), 0.0f);
		fd.shape = &shape;
		fd.friction = 1;
		fd.density = 1;
		myBody->CreateFixture(&fd)->SetUserData((void*)getGameObject());
	}
	else if (shapeType == RandomShape2DType::Circle) {
		b2CircleShape shape;
		shape.m_radius = SDL_max(scale.x / 2, scale.y / 2);
		fd.shape = &shape;
		fd.friction = 1;
		fd.density = 1;
		myBody->CreateFixture(&fd)->SetUserData((void*)getGameObject());
	}
	myBody->SetTransform(b2Vec2(position.x, position.y), rZ * DEG_TO_RAD);
	myBody->SetType(bodyType);
}

Body2DCmp::~Body2DCmp() {
	RandomPhysics2D::world->DestroyBody(myBody);
	myBody = nullptr;
}
