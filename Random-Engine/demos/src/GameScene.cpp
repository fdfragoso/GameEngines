#include "RandomEngine.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "GameScene.hpp"
//Include your custom scripts
#include "PlayerController.hpp"
#include "ParallaxController.hpp"
#include "SpawnController.hpp"

#include <iostream>

using namespace std;

void GameScene::load() {
	//For physics
	int LAYER_DEFAULT = 0x0001;
	int LAYER_ENVIROMENT_COLLIDER = 0x0002;
	int LAYER_ENVIROMENT = 0x0004;
	int LAYER_GROUND= 0x0008;
	b2Filter filter;

	//Add your resources
	RandomEngine::spriteAtlas->addFromFile("data/game/", "gamePj.json");
	RandomEngine::spriteAtlas->addFromFile("data/game/", "gameSprites.json");

	//Set camera settings here
	auto sre = SRE::SimpleRenderEngine::instance;
	sre->getCamera()->setOrthographicProjection(0, RandomEngine::width / 20, 0, RandomEngine::height / 20, 0.1f, 50.0f);
	sre->getCamera()->lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	Sprite * fJump = RandomEngine::spriteAtlas->getSprite("salto");
	Sprite * fRun1 = RandomEngine::spriteAtlas->getSprite("correr1");
	Sprite * fRun2 = RandomEngine::spriteAtlas->getSprite("correr2");
	Sprite * fRun3 = RandomEngine::spriteAtlas->getSprite("correr3");

	Sprite * ground = RandomEngine::spriteAtlas->getSprite("ground");

	Sprite * tree1 = RandomEngine::spriteAtlas->getSprite("tree1");
	Sprite * tree2 = RandomEngine::spriteAtlas->getSprite("tree2");

	Sprite * house1 = RandomEngine::spriteAtlas->getSprite("house1");
	Sprite * house2 = RandomEngine::spriteAtlas->getSprite("house2");

	Sprite * ITU = RandomEngine::spriteAtlas->getSprite("ITU");

	Sprite * bicycle1 = RandomEngine::spriteAtlas->getSprite("bicycle1");
	Sprite * bicycle2 = RandomEngine::spriteAtlas->getSprite("bicycle2");
	Sprite * bicycle3 = RandomEngine::spriteAtlas->getSprite("bicycle3");
	Sprite * bicycle4 = RandomEngine::spriteAtlas->getSprite("bicycle4");
	Sprite * bicycle5 = RandomEngine::spriteAtlas->getSprite("bicycle5");
	Sprite * bicycle6 = RandomEngine::spriteAtlas->getSprite("bicycle6");
	Sprite * bicycle7 = RandomEngine::spriteAtlas->getSprite("bicycle7");
	
	Sprite * fox = RandomEngine::spriteAtlas->getSprite("fox");

	Sprite * car1 = RandomEngine::spriteAtlas->getSprite("car1");
	Sprite * car2 = RandomEngine::spriteAtlas->getSprite("car2");

	Sprite * mutalisk1 = RandomEngine::spriteAtlas->getSprite("mutalisk1");
	Sprite * mutalisk2 = RandomEngine::spriteAtlas->getSprite("mutalisk2");
	Sprite * mutalisk3 = RandomEngine::spriteAtlas->getSprite("mutalisk3");
	Sprite * mutalisk4 = RandomEngine::spriteAtlas->getSprite("mutalisk4");
	Sprite * mutalisk5 = RandomEngine::spriteAtlas->getSprite("mutalisk5");

	//Creating aux var
	std::shared_ptr<TransformCmp> transformCmp = nullptr; 
	std::shared_ptr<SpriteRendererCmp> spriteCmp = nullptr; 
	std::shared_ptr<AnimationCmp> animCmp = nullptr;
	std::shared_ptr<Body2DCmp> bodyCmp = nullptr;
	float maxVel = -60;
	
	//Creating ITU
	auto x = this->addGameObject("ITU");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 30,13,0 });
	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(ITU, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.05,0.07,1 });


	//Creating right collider for parallax objects
	x = this->addGameObject("parallaxC");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({-3, 4, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,7,1 };
	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_staticBody);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.categoryBits = LAYER_ENVIROMENT_COLLIDER;
		filter.maskBits = LAYER_ENVIROMENT | LAYER_DEFAULT;
		f->SetFilterData(filter);
	}

	//Creating right collider for parallax objects
	x = this->addGameObject("parallaxCRight");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 45, 20, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,2,1 };
	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_staticBody);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.categoryBits = LAYER_ENVIROMENT_COLLIDER;
		filter.maskBits = LAYER_ENVIROMENT | LAYER_DEFAULT;
		f->SetFilterData(filter);
	}

	//Houses Far
	for (int i = 0; i < 8; i++) {
		x = this->addGameObject("house_back" + std::to_string(i));
		transformCmp = x->addComponent<TransformCmp>();
		transformCmp->setPosition({ i * 4.5 + 2, 11, 0 });
		transformCmp->setRotation({ 0, 0, 0 });
		transformCmp->scale = { 1,1,1 };

		spriteCmp = x->addComponent<SpriteRendererCmp>();
		spriteCmp->setUp(house1, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.08, 0.13, 1 });

		bodyCmp = x->addComponent<Body2DCmp>();
		bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
		for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
			filter = f->GetFilterData();
			filter.categoryBits = LAYER_ENVIROMENT;
			filter.maskBits = LAYER_ENVIROMENT_COLLIDER;
			f->SetFilterData(filter);
		}
		bodyCmp->myBody->SetLinearVelocity({ maxVel * 1 / 8, 0 });
		bodyCmp->myBody->SetGravityScale(0);

		x->addComponent<ParallaxController>()->movVel = maxVel * 1 / 8;
	}
	
	//Tree2
	for (int i = 0; i < 5; i++) {
		x = this->addGameObject("tree2_" + std::to_string(i));
		transformCmp = x->addComponent<TransformCmp>();
		transformCmp->setPosition({ i * 7 + 2, 9, 0 });
		transformCmp->setRotation({ 0, 0, 0 });
		transformCmp->scale = { 1,1,1 };

		spriteCmp = x->addComponent<SpriteRendererCmp>();
		spriteCmp->setUp(tree2, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

		bodyCmp = x->addComponent<Body2DCmp>();
		bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
		for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
			filter = f->GetFilterData();
			filter.categoryBits = LAYER_ENVIROMENT;
			filter.maskBits = LAYER_ENVIROMENT_COLLIDER;
			f->SetFilterData(filter);
		}
		bodyCmp->myBody->SetLinearVelocity({ maxVel * 2 / 7, 0 });
		bodyCmp->myBody->SetGravityScale(0);

		x->addComponent<ParallaxController>()->movVel = maxVel * 2 / 7;
	}

	//Houses Close
	for (int i = 0; i < 3; i++) {
		x = this->addGameObject("house" + std::to_string(i));
		transformCmp = x->addComponent<TransformCmp>();
		transformCmp->setPosition({ i * 11 + 2, 10, 0 });
		transformCmp->setRotation({ 0, 0, 0 });
		transformCmp->scale = { 1,1,1 };

		spriteCmp = x->addComponent<SpriteRendererCmp>();
		spriteCmp->setUp(house1, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.1, 0.13, 1 });

		bodyCmp = x->addComponent<Body2DCmp>();
		bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
		for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
			filter = f->GetFilterData();
			filter.categoryBits = LAYER_ENVIROMENT;
			filter.maskBits = LAYER_ENVIROMENT_COLLIDER;
			f->SetFilterData(filter);
		}
		bodyCmp->myBody->SetLinearVelocity({ maxVel * 3 / 7,  0 });
		bodyCmp->myBody->SetGravityScale(0);

		x->addComponent<ParallaxController>()->movVel = maxVel * 3 / 7;
	}

	//Tree1
	for (int i = 0; i < 4; i++) {
		x = this->addGameObject("tree1_" + std::to_string(i));
		transformCmp = x->addComponent<TransformCmp>();
		transformCmp->setPosition({ i * 9 + 2, 7, 0 });
		transformCmp->setRotation({ 0, 0, 0 });
		transformCmp->scale = { 1,1,1 };

		spriteCmp = x->addComponent<SpriteRendererCmp>();
		spriteCmp->setUp(tree1, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.08, 1 });

		bodyCmp = x->addComponent<Body2DCmp>();
		bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
		for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
			filter = f->GetFilterData();
			filter.categoryBits = LAYER_ENVIROMENT;
			filter.maskBits = LAYER_ENVIROMENT_COLLIDER;
			f->SetFilterData(filter);
		}
		bodyCmp->myBody->SetLinearVelocity({ maxVel, 0 });
		bodyCmp->myBody->SetGravityScale(0);

		x->addComponent<ParallaxController>()->movVel = maxVel;
	}
	//Ground sprite
	//parent
	x = this->addGameObject("GroundSprite");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 16, 4, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };
	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(ground, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07,0.04,1 });


	//Ground collider
	x = this->addGameObject("groundC");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 2,2.5,0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 4,0.2,1 };

	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_staticBody);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.categoryBits = LAYER_GROUND;
		f->SetFilterData(filter);
	}

	//Creating F
	x = this->addGameObject("player");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 5, 3.7, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(nullptr, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.012, 0.012, 1 });

	animCmp = x->addComponent<AnimationCmp>();
	animCmp->createAnim("run", new Animation({ fRun2, fRun1, fRun2, fRun3 }, 500));
	animCmp->createAnim("jump", new Animation({ fJump }, 10));
	animCmp->setAnim("run");

	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
	bodyCmp->myBody->SetGravityScale(5);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.maskBits = LAYER_GROUND | LAYER_DEFAULT;
		f->SetFilterData(filter);
	}
	x->addComponent<PlayerController>();

	//Creating Bicycle
	x = this->addGameObject("foxOnBike");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 20, 4.5, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(nullptr, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

	animCmp = x->addComponent<AnimationCmp>();
	animCmp->createAnim("run", new Animation({ bicycle1, bicycle2, bicycle3, bicycle4, bicycle5, bicycle6, bicycle7 }, 500));
	animCmp->setAnim("run");

	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
	bodyCmp->myBody->SetGravityScale(0);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.maskBits = LAYER_ENVIROMENT_COLLIDER | LAYER_DEFAULT;
		f->SetFilterData(filter);
	}
	auto sc1 = x->addComponent<SpawnController>();
	sc1->setVel(-7.5, -55);
	sc1->initPos = glm::vec3(35, 4.5, 0);

	auto y = this->addGameObject("fox");
	transformCmp = y->addComponent<TransformCmp>();
	transformCmp->setPosition({ 0, 0.3, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	spriteCmp = y->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(fox, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

	transformCmp->parent = x.get();
	x->getComponent<TransformCmp>()->childs.push_back(y);
	
	//Creating Car
	x = this->addGameObject("car1");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ 25, 2, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 3,1,1 };

	spriteCmp = x->addComponent<SpriteRendererCmp>();
	transformCmp->scale = { 1,1,1 };
	spriteCmp->setUp(car1, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });

	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
	bodyCmp->myBody->SetGravityScale(0);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.maskBits = LAYER_ENVIROMENT_COLLIDER | LAYER_DEFAULT;
		f->SetFilterData(filter);
	}

	auto sc2 = x->addComponent<SpawnController>();
	sc2->setVel(-10, -15);
	sc2->initPos = glm::vec3(35, 2, 0);

	//Creating Mutalisk
	x = this->addGameObject("mutalisk");
	transformCmp = x->addComponent<TransformCmp>();
	transformCmp->setPosition({ -2, 20, 0 });
	transformCmp->setRotation({ 0, 0, 0 });
	transformCmp->scale = { 1,1,1 };

	spriteCmp = x->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(nullptr, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07, 0.07, 1 });
	
	animCmp = x->addComponent<AnimationCmp>();
	animCmp->createAnim("fly", new Animation({ mutalisk1, mutalisk2, mutalisk3, mutalisk4, mutalisk5 }, 500));
	animCmp->setAnim("fly");

	bodyCmp = x->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
	bodyCmp->myBody->SetGravityScale(0);
	for (b2Fixture* f = bodyCmp->myBody->GetFixtureList(); f; f = f->GetNext()) {
		filter = f->GetFilterData();
		filter.maskBits = LAYER_ENVIROMENT_COLLIDER | LAYER_DEFAULT;
		f->SetFilterData(filter);
	}

	auto sc = x->addComponent<SpawnController>();
	sc->setVel(30, 35);
	sc->initPos = glm::vec3(-2, 20, 0);
}