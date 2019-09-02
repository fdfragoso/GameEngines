#include "RandomEngine.hpp"
#include <iostream>
#include <time.h>

#include "GameObjectParser.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "RandomInterpolation.hpp"

using namespace glm;
using namespace SRE;

float RandomEngine::width = 0;
float RandomEngine::height = 0;
float RandomEngine::deltaTimeSec = 0;
bool RandomEngine::quit = false;
bool RandomEngine::physicsDebugMode = false;
bool RandomEngine::pauseEngine = false;
ParticleRandomMat * RandomEngine::particleMat = nullptr;
DefaultRandomMat * RandomEngine::defaultMat = nullptr;
SpriteDefaultMat * RandomEngine::spriteDefaultMat = nullptr;
AlphaBlendMat * RandomEngine::alphaBlendMat = nullptr;
SpriteAtlas * RandomEngine::spriteAtlas = nullptr;
Scene * RandomEngine::currentScene = nullptr;
std::vector<GameObject * > RandomEngine::toDestroy = {};

RandomEngine::RandomEngine(SDL_Window* window, float width, float height, bool debugMode) {
	this->window = window;
    this->width = width;
    this->height = height;
	this->debugMode = debugMode;
	this->physicsDebugMode = debugMode;
	quadMesh = nullptr;
	sphereMesh = nullptr;
	cubeMesh = nullptr;
	currentScene = nullptr;

	spriteAtlas = new SpriteAtlas();
	//Initializing Random Physics 2D
	randomPhysics2D.startRandomPhysics2D();
	//Initializing SRE and setting default camera values
	sre = new SRE::SimpleRenderEngine(window);
	sre->getCamera()->setOrthographicProjection(0, width, 0, height, 0.1f, 50.0f);
	sre->getCamera()->lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//Creating default materials
	createDefaultMaterials();
	//Initializing Random GUI
	randomGUI.startRandomGUI(window);
	if (debugMode) {
		std::cout << "Debug Mode: Press 'R' to show Random Engine Debug Window" << std::endl;
	}
}

RandomEngine::~RandomEngine() {
	pauseEngine = true;
	randomInput.onQuitClear();
	SceneManager::deleteAllScenes();
	currentScene = nullptr;
	delete quadMesh;
	delete sphereMesh;
	delete cubeMesh;
	delete currentScene;
	randomPhysics2D.stopRandomPhysics2D();

	delete alphaBlendMat;
	delete spriteDefaultMat;
	delete defaultMat;
	delete particleMat;

	delete spriteAtlas;
	sre->~SimpleRenderEngine();
}

void RandomEngine::startGameLoop() {
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    quit = false;
    while (!quit){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		sre->clearScreen({ 0.35, 0.57, 0.98, 1 });

		//Deleting objects in queue
		if (pauseEngine) {
			while (randomPhysics2D.world->IsLocked()) {
				continue;
			}
			for (auto d : toDestroy) {
				d->~GameObject();
			}
			if (SceneManager::haveToLoad) {
				SceneManager::loadResources();
				//Calls Start() on game objects
				for (int i = 0; i < currentScene->getSize(); i++) {
					auto & go = currentScene->getGameObject(i);
					go->scriptStart();
				}
			}
			RandomEngine::pauseEngine = false;
		}

		//Updates RandomInput
		SDL_PumpEvents();
		randomInput.checkInput();
		//Handles sdl events
		HandleSDLEvents();
		//Debug window interaction
		if (debugMode && randomInput.getKeyDown(SDLK_r)) {
			randomGUI.showDebugGUI = randomGUI.showDebugGUI ? false : true;
		}
		//Calls Update() on game objects
		for (int i = 0; i < currentScene->getSize(); i++) {
			auto & go = currentScene->getGameObject(i);
			go->scriptUpdate(deltaTimeSec);
		}

		//Updates colliders position
		for (int i = 0; i < currentScene->getSize(); i++) {
			auto & go = currentScene->getGameObject(i);
			go->updateCollider();
		}

		//Triggers a physic step
		randomPhysics2D.world->Step(1 / 60.f, 10, 10);

		//Physcis debug draw
		if (physicsDebugMode) {
			randomPhysics2D.world->DrawDebugData();
		}

		//Renders game objects and updates transforms
		for (int i = 0; i < currentScene->getSize(); i++) {
			auto & go = currentScene->getGameObject(i);
			go->updateGlobalTransform();
			go->draw();
		}
		//Renders GUI
		randomGUI.update();
		sre->swapWindow();
        SDL_Delay(16);
    }
	randomGUI.shutDown();
}

void RandomEngine::HandleSDLEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		randomGUI.handleEvent(&event);
	}
}

void RandomEngine::createDefaultMaterials() {
	quadMesh = Mesh::createQuad();
	sphereMesh = Mesh::createSphere();
	cubeMesh = Mesh::createCube();
	//Init Materials
	particleMat = new ParticleRandomMat();
	defaultMat = new DefaultRandomMat();
	spriteDefaultMat = new SpriteDefaultMat();
	alphaBlendMat = new AlphaBlendMat();
}


void RandomEngine::setScene(Scene * newScene) {
	currentScene = newScene;
}

void RandomEngine::quitGameLoop() {
	quit = true;
}