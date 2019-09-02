#include "RandomEngine.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "Demo02.hpp"
//Include your custom scripts
#include "SpamController.hpp"

#include <iostream>

using namespace std;

void Demo02::load() {
	//Add your resources
	RandomEngine::spriteAtlas->addFromFile("data/", "MarioPacked.json");
	//Set camera settings here
	auto sre = SRE::SimpleRenderEngine::instance;
	sre->getCamera()->setOrthographicProjection(0, RandomEngine::width / 20, 0, RandomEngine::height / 20, 0.1f, 50.0f);
	sre->getCamera()->lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	//Load from file first, before creating custom obj
	addFromFile("data/techdemo.json");
	
	//Creating GM
	auto x = this->addGameObject("GM");
	x->addComponent<TransformCmp>();
	x->addComponent<SpamController>();

}