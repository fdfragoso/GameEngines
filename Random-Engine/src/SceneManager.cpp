//
// Created by Random Engine on 10/11/16.
//

#include "SceneManager.hpp"
#include "RandomEngine.hpp"

using namespace std;

std::vector<Scene *> SceneManager::scenes = {};
Scene * SceneManager::currentScene = nullptr;
int SceneManager::currentIndex = 0;
bool SceneManager::haveToLoad = false;

void SceneManager::addScene(Scene *newScene) {
	scenes.push_back(newScene);
}

void SceneManager::loadScene(int index) {
	RandomEngine::pauseEngine = true;
	currentIndex = index;
	haveToLoad = true;
}

//This is supposed to be called after load scene
void SceneManager::loadResources() {
	if (currentScene != nullptr) {
		currentScene->removeAllGameObjects();
		RandomEngine::spriteAtlas->clearAtlas();
	}
	currentScene = scenes[currentIndex];
	currentScene->load();
	RandomGUI::setScene(currentScene);
	RandomEngine::setScene(currentScene);
	haveToLoad = false;
}

void SceneManager::deleteAllScenes() {
	currentScene = nullptr;
	delete currentScene;
	for (auto e : scenes) {
		e->removeAllGameObjects();
		delete e;
	}
	scenes.clear();
}