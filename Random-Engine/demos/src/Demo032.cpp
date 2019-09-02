#include "RandomEngine.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "Demo032.hpp"
//Include your custom scripts
#include "Demo3C2.hpp"

#include <iostream>

using namespace std;

void Demo032::load() {
	//Creating GM
	auto x = this->addGameObject("GM");
	x->addComponent<TransformCmp>();
	x->addComponent<Demo3C2>();

	for (int i = 0; i < 70000; i++) {
		x = this->addGameObject("dummy");
		x->addComponent<TransformCmp>();
		//Add from file calls SRE::Texture::createFromFile(), which creates a memory leak per use
		//RandomEngine::spriteAtlas->addFromFile("data/", "MarioPacked.json");
	}
}