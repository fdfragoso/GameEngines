#include "RandomEngine.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "Demo03.hpp"
//Include your custom scripts
#include "Demo3C1.hpp"

#include <iostream>

using namespace std;

void Demo03::load() {
	//Set camera settings here
	auto sre = SRE::SimpleRenderEngine::instance;
	sre->getCamera()->setOrthographicProjection(0, RandomEngine::width / 20, 0, RandomEngine::height / 20, 0.1f, 50.0f);
	sre->getCamera()->lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//Creating GM
	auto x = this->addGameObject("GM");
	x->addComponent<TransformCmp>();
	x->addComponent<Demo3C1>();
}