#include "RandomEngine.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "Demo01.hpp"
//Include your custom scripts
#include "MarioController.hpp"

#include <iostream>

using namespace std;

void Demo01::load() {
	//Add your resources
	RandomEngine::spriteAtlas->addFromFile("data/", "MarioPacked.json");
	//Set camera settings here
	auto sre = SRE::SimpleRenderEngine::instance;
	sre->getCamera()->setOrthographicProjection(0, RandomEngine::width / 20, 0, RandomEngine::height / 20, 0.1f, 50.0f);
	sre->getCamera()->lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	Sprite * brick0 = RandomEngine::spriteAtlas->getSprite("brick");

	Sprite * marioI = RandomEngine::spriteAtlas->getSprite("mario_0");
	Sprite * marioJ = RandomEngine::spriteAtlas->getSprite("mario_6");

	Sprite * mario2 = RandomEngine::spriteAtlas->getSprite("mario_2");
	Sprite * mario5 = RandomEngine::spriteAtlas->getSprite("mario_5");
	Sprite * mario7 = RandomEngine::spriteAtlas->getSprite("mario_7");

	Sprite * cloud0 = RandomEngine::spriteAtlas->getSprite("cloud_0");
	Sprite * cloud1 = RandomEngine::spriteAtlas->getSprite("cloud_1");
	Sprite * plant0 = RandomEngine::spriteAtlas->getSprite("green_plant_0");
	Sprite * plant1 = RandomEngine::spriteAtlas->getSprite("green_plant_1");
	Sprite * plant2 = RandomEngine::spriteAtlas->getSprite("green_plant_2");
	Sprite * plant3 = RandomEngine::spriteAtlas->getSprite("green_plant_3");
	Sprite * mushroom0 = RandomEngine::spriteAtlas->getSprite("mushroom_y0");
	Sprite * mushroom1 = RandomEngine::spriteAtlas->getSprite("mushroom_y1");
	Sprite * mushroom2 = RandomEngine::spriteAtlas->getSprite("mushroom_y2");
	Sprite * mushroom3 = RandomEngine::spriteAtlas->getSprite("mushroom_y3");
	Sprite * mushroom4 = RandomEngine::spriteAtlas->getSprite("mushroom_y4");
	Sprite * mushroom5 = RandomEngine::spriteAtlas->getSprite("mushroom_y5");
	Sprite * tube0 = RandomEngine::spriteAtlas->getSprite("green_tube");

	//Creating Mario
	auto x = this->addGameObject("mario");
	auto transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 5, 3.2, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	auto spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(nullptr, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

	auto animCmp = x->addComponent<AnimationCmp>();
	animCmp->createAnim("walk", new Animation({ mario2,mario7,mario2,mario5 }, 500));
	animCmp->createAnim("jump", new Animation({ marioJ }, 10));
	animCmp->createAnim("idle", new Animation({ marioI}, 10));
	animCmp->setAnim("idle");

	x->addComponent<MarioController>();
	//Mushroom
	x = this->addGameObject("mushroom");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 15,3.2,0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(nullptr, RandomEngine::alphaBlendMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

	animCmp = x->addComponent<AnimationCmp>();
	animCmp->createAnim("mushroom", new Animation({ mushroom0, mushroom1, mushroom2, mushroom3, mushroom4, mushroom5 }, 6000));
	animCmp->setAnim("mushroom");
	//Plant
	x = this->addGameObject("plant");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 25,7.5,0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(nullptr, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

	animCmp = x->addComponent<AnimationCmp>();
	animCmp->createAnim("plant", new Animation({ plant0, plant1, plant2, plant3 }, 1000));
	animCmp->setAnim("plant");
	//Creating bricks
	//parent
	x = this->addGameObject("floor0");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 5,1,0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	for (int i = 0; i < 16; i++) {
		auto y = this->addGameObject("brick" + std::to_string(i));
		transformCmp = y->addComponent<TransformCmp>();
		transformCmp->setPosition({ i * 2 -4,-0.05, 0 });
		x->getComponent<TransformCmp>()->childs.push_back(y);
		y->getComponent<TransformCmp>()->parent = x.get();
		auto spriteY = y->addComponent<SpriteRendererCmp>();
		spriteY->setUp(brick0, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07,0.07,1 });
	}

	//Creating clouds
	x = this->addGameObject("cloud0");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 5,13,0 });
	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(cloud0, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.1,0.07,1 });

	x = this->addGameObject("cloud1");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 20,18,0 });
	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(cloud1, RandomEngine::alphaBlendMat, { 1,1,1,1 }, { 0.1,0.07,1 });

	//Creating tube
	x = this->addGameObject("tube0");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 25,4,0 });
	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(tube0, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07,0.07,1 });
}