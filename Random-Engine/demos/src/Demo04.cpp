#include "RandomEngine.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "Demo04.hpp"
//Include your custom scripts
#include "ParticleController.hpp"
#include <iostream>

using namespace std;

void Demo04::load() {
	//Add your resources
	RandomEngine::spriteAtlas->addFromFile("data/", "MarioPacked.json");
	//Set camera settings here
	auto sre = SRE::SimpleRenderEngine::instance;
	sre->getCamera()->setOrthographicProjection(0, RandomEngine::width / 20, 0, RandomEngine::height / 20, 0.1f, 50.0f);
	sre->getCamera()->lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	//Load from file first, before creating custom obj
	
	//Creating Particles
	auto x = this->addGameObject("Particles");
	x->addComponent<TransformCmp>();
	x->getComponent<TransformCmp>()->setPosition({ 15, 15, 0 });
	x->addComponent<ParticleEmitterCmp>();
	SRE::Texture * myTex = nullptr;
	x->getComponent<ParticleEmitterCmp>()->setColor(glm::vec4{ 0.5, 0, 0, 1 }, glm::vec4{0, 0.5, 0, 1}, InterpolationType::Linear);
	x->getComponent<ParticleEmitterCmp>()->setUp(1024, myTex);
	x->addComponent<ParticleController>();
}
