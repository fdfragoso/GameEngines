#include "BirdGame.hpp"
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"

#include <iostream>
#include "sre/Profiler.hpp"
#include "SpriteComponent.hpp"
#include "SpriteAnimationComponent.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "PhysicsComponent.hpp"
#include "BirdController.hpp"
#include "SDL_mixer.h"

using namespace std;
using namespace sre;

const glm::vec2 BirdGame::windowSize(400,600);

BirdGame* BirdGame::instance = nullptr;

BirdGame::BirdGame()
        :debugDraw(physicsScale)
{
    instance = this;
    r.setWindowSize(windowSize);
    r.init(SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL, false);

    init();

    // setup callback functions
    r.keyEvent = [&](SDL_Event& e){
        onKey(e);
    };
    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };
    r.frameRender = [&](){
        render();
    };
    // start game loop
    r.startEventLoop();
}

void BirdGame::init() {
	
	if (coinCount > highScore)
		highScore = coinCount;
	coinCount = 0;

	if (world)
		world->SetContactListener(nullptr);
    sceneObjects.clear();
	camera.reset();
	myBird.reset();
    physicsComponentLookup.clear();
    initPhysics();
    auto camObj = createGameObject();
    camObj->name = "Camera";
    camera = camObj->addComponent<SideScrollingCamera>();
    camObj->setPosition(windowSize*0.5f);
	if(!spriteAtlas)
		spriteAtlas = SpriteAtlas::create("bird.json","bird.png");

    auto birdObj = createGameObject();
    birdObj->name = "Bird";
	myBird = birdObj;
    camera->setFollowObject(birdObj, {+150,BirdGame::windowSize.y/2});
    auto so = birdObj->addComponent<SpriteComponent>();
    auto sprite = spriteAtlas->get("bird1.png");
    sprite.setScale({2,2});

    birdObj->setPosition({-100,300});
    so->setSprite(sprite);
    auto anim = birdObj->addComponent<SpriteAnimationComponent>();
    auto phys = birdObj->addComponent<PhysicsComponent>();
    phys->initCircle(b2_dynamicBody, 10/physicsScale, {birdObj->getPosition().x/physicsScale,birdObj->getPosition().y/physicsScale}, 1);
    auto birdC = birdObj->addComponent<BirdController>();

    vector<Sprite> spriteAnim({spriteAtlas->get("bird1.png"),spriteAtlas->get("bird2.png"),spriteAtlas->get("bird3.png"),spriteAtlas->get("bird2.png")});
    for(auto & s : spriteAnim){
        s.setScale({2,2});
    }
    anim-> setSprites(spriteAnim);

    auto spriteBottom = spriteAtlas->get("column_bottom.png");
    spriteBottom.setScale({2,2});
    float curve = 250;
    int length = 50;
    float heighVariation = 80;
    float xVariation = 50;

    for (int i=0;i<length;i++) {
        auto obj = createGameObject();
        obj->name = "Wall bottom";
        auto so = obj->addComponent<SpriteComponent>();

        float xOffset = xVariation * cos(i*curve*0.2f);
        glm::vec2 pos{i*300+xOffset,spriteBottom.getSpriteSize().y/2 + sin(i*curve)*heighVariation};
        obj->setPosition(pos);
        so->setSprite(spriteBottom);
        glm::vec2 s { spriteBottom.getSpriteSize().x * spriteBottom.getScale().x/2, spriteBottom.getSpriteSize().y * spriteBottom.getScale().y/2};
		
		//Adding colliders to walls
		auto phys = obj->addComponent<PhysicsComponent>();
		phys->initBox(b2_staticBody, s/physicsScale, { pos.x / physicsScale, pos.y / physicsScale }, 0.0f);
		
	}
    auto spriteTop = spriteAtlas->get("column_top.png");
    spriteTop.setScale({2,2});
    for (int i=0;i<length;i++){
        auto obj = createGameObject();
        obj->name = "Wall top";
        auto so = obj->addComponent<SpriteComponent>();
        float xOffset = xVariation * cos(i*curve*0.2f);
        glm::vec2 pos{ i*300+xOffset, windowSize.y-spriteTop.getSpriteSize().y/2 + sin(i*curve)*heighVariation};
        obj->setPosition(pos);
        glm::vec2 s { spriteTop.getSpriteSize().x * spriteTop.getScale().x/2, spriteTop.getSpriteSize().y * spriteTop.getScale().y/2};
        so->setSprite(spriteTop);

		//Adding colliders to walls
		auto phys = obj->addComponent<PhysicsComponent>();
		phys->initBox(b2_staticBody, s/physicsScale, { pos.x/physicsScale, pos.y/physicsScale}, 0.0f);

		//Adding Coins
		float maxY = 0.8f * windowSize.y;
		float minY = 0.3f * windowSize.y;
		float randY = minY + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxY - minY)));
		glm::vec2 coinPos{ i * 300 + xOffset + 150, randY };
		auto spriteCoin = spriteAtlas->get("coin.png");
		spriteCoin.setScale({1,1});
		auto coinObj = createGameObject();
		coinObj->name = "Coin";
		auto coinSpriteComponent = coinObj->addComponent<SpriteComponent>();
		coinSpriteComponent->setSprite(spriteCoin);
		coinObj->setPosition(coinPos);
		auto coinPhysics = coinObj->addComponent<PhysicsComponent>();
		glm::vec2 coinScale { spriteCoin.getSpriteSize().x * spriteCoin.getScale().x / 2, spriteCoin.getSpriteSize().y * spriteCoin.getScale().y / 2 };
		coinPhysics->initCircle(b2_staticBody, coinScale.x/physicsScale, coinPos/physicsScale, 0.0f);
		coinPhysics->setSensor(true);
    }


	if (coinSound == nullptr) 
	{
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			std::cout << "Cannot initialize audio output" << std::endl;
			return;
		}
		coinSound = Mix_LoadWAV("coin_collect.wav");
	}

	if (!background1Component.isInitialized()) 
	{
		background1Component.init("background.png");
		background2Component.init("background2.png");
	}
}

void BirdGame::update(float time) {

    if (gameState == GameState::Running){
        updatePhysics();
    }
    for (int i=0;i<sceneObjects.size();i++){
        sceneObjects[i]->update(time);
    }
}

void BirdGame::render() {
    auto rp = RenderPass::create()
            .withCamera(camera->getCamera())
            .build();

	//static Profiler profiler;
	//profiler.update();
	//profiler.gui();

    auto pos = camera->getGameObject()->getPosition();
    background1Component.renderBackground(rp, +pos.x*0.8f);

    auto spriteBatchBuilder = SpriteBatch::create();
    for (auto & go : sceneObjects){
        go->renderSprite(spriteBatchBuilder);
    }

    if (gameState == GameState::Ready){
        auto sprite = spriteAtlas->get("get-ready.png");
        sprite.setPosition(pos);
        spriteBatchBuilder.addSprite(sprite);
    } else if (gameState == GameState::GameOver){
        auto sprite = spriteAtlas->get("game-over.png");
        sprite.setPosition(pos);
        spriteBatchBuilder.addSprite(sprite);
    }

    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);

    background2Component.renderBackground(rp, -pos.x*0.2f);

    if (doDebugDraw){
        world->DrawDebugData();
        rp.drawLines(debugDraw.getLines());
        debugDraw.clear();
    }
	//START GUI
	float winWidth = 140;
	ImGui::SetNextWindowPos(ImVec2((Renderer::instance->getWindowSize().x - winWidth)*0.5f, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(winWidth, 70), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::TextColored(ImVec4(1.0f, 0.41f, 0.1f, 1.0f), "HIGH S: %i", highScore);
	ImGui::Text("SCORE: %i", coinCount);
	ImGui::SetWindowFontScale(1.5f);
	
	//ImGui::LabelText("Score", "%i");
	//ImGui::LabelText("SnakeBody#", "%i", SnakeBody::totalSnakeBodies);
	ImGui::End();
	//END GUI
}

void BirdGame::onKey(SDL_Event &event) {
    for (auto & gameObject: sceneObjects) {
        for (auto & c : gameObject->getComponents()){
            bool consumed = c->onKey(event);
            if (consumed){
                return;
            }
        }
    }

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_d:
                // press 'd' for physics debug
                doDebugDraw = !doDebugDraw;
                if (doDebugDraw){
                    world->SetDebugDraw(&debugDraw);
                } else {
                    world->SetDebugDraw(nullptr);
                }
                break;
            case SDLK_r:
                init();
                break;
            case SDLK_SPACE:
                if (gameState == GameState::GameOver){
                    init();
                    gameState = GameState::Ready;
                } else if (gameState == GameState::Ready){
                    gameState = GameState::Running;
                }
                break;

        }
    }
}

std::shared_ptr<GameObject> BirdGame::createGameObject() {
    auto obj = shared_ptr<GameObject>(new GameObject());
    sceneObjects.push_back(obj);
    return obj;
}

void BirdGame::updatePhysics() {
	float birdY = myBird->getPosition().y;

	if (birdY > (1.0f * windowSize.y) || birdY < (0.24f * windowSize.y))
	{
		setGameState(GameState::GameOver);
	}

    const float32 timeStep = 1.0f / 60.0f;
    const int positionIterations = 2;
    const int velocityIterations = 6;
    world->Step(timeStep, velocityIterations, positionIterations);

    for (auto phys : physicsComponentLookup){
        if (phys.second->rbType == b2_staticBody) continue;
        auto position = phys.second->body->GetPosition();
        float angle = phys.second->body->GetAngle();
        auto gameObject = phys.second->getGameObject();
        gameObject->setPosition(glm::vec2(position.x*physicsScale, position.y*physicsScale));
        gameObject->setRotation(angle);
    }
}

void BirdGame::initPhysics() {
    float gravity = -9.8; // 9.8 m/s2
    delete world;
    world = new b2World(b2Vec2(0,gravity));
    world->SetContactListener(this);

    if (doDebugDraw){
        world->SetDebugDraw(&debugDraw);
    }
}

void BirdGame::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);
    handleContact(contact, true);
}

void BirdGame::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
    handleContact(contact, false);
}

void BirdGame::deregisterPhysicsComponent(PhysicsComponent *r) {
    auto iter = physicsComponentLookup.find(r->fixture);
    if (iter != physicsComponentLookup.end()){
        physicsComponentLookup.erase(iter);
    } else {
        assert(false); // cannot find physics object
    }
}

void BirdGame::registerPhysicsComponent(PhysicsComponent *r) {
    physicsComponentLookup[r->fixture] = r;
}

void BirdGame::handleContact(b2Contact *contact, bool begin) {
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    PhysicsComponent* physA = physicsComponentLookup[fixA];
    PhysicsComponent* physB = physicsComponentLookup[fixB];
    auto & aComponents = physA->getGameObject()->getComponents();
    auto & bComponents = physB->getGameObject()->getComponents();
    for (auto & c : aComponents){
        if (begin){
            c->onCollisionStart(physB);
        } else {
            c->onCollisionEnd(physB);
        }
    }
    for (auto & c : bComponents){
        if (begin){
            c->onCollisionStart(physA);
        } else {
            c->onCollisionEnd(physA);
        }
    }
}

void BirdGame::setGameState(GameState newState) {
    this->gameState = newState;
}

void BirdGame::coinCollected()
{
	coinCount++;
	if (coinSound != nullptr)
	{
		Mix_PlayChannel(-1, coinSound, 0);
	}
	else { std::cout << "DIDN'T FIND SOUND" << std::endl; }
}
