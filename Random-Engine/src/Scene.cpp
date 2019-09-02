
#include "Scene.hpp"
#include "GameObjectParser.hpp"
#include "RandomEngine.hpp"

#include <iostream>

using namespace std;

std::shared_ptr<GameObject> Scene::addGameObject(std::string name) {
    auto res = make_shared<GameObject>(GameObject(name));
    gameObjects.push_back(res);
    return res;
}

bool Scene::removeGameObject(std::shared_ptr<GameObject> ptr) {
    for (auto iter = gameObjects.begin();iter != gameObjects.end(); iter++){
        if (*iter == ptr){
			RandomEngine::pauseEngine = true;
			RandomEngine::toDestroy.push_back(iter->get());
            return true;
        }
    }
    return false;
}

int Scene::getSize() {
    return (int) gameObjects.size();
}

std::shared_ptr<GameObject> Scene::getGameObject(int index) {
    return gameObjects.at(index);
}

std::shared_ptr<GameObject> Scene::getGameObject(std::string name) {
	for (int i = 0; i < getSize(); i++) {
		if (gameObjects[i]->getName() == name) {
			return gameObjects[i];
		}
	}
	return nullptr;
}

void Scene::removeAllGameObjects() {
	gameObjects.clear();
}

void Scene::load() {
}


void Scene::addFromFile(std::string file) {
	std::vector<GameObjectDescriptor> parsedGO = GameObjectParser::parseFile(file);
	for (int i = 0; i < parsedGO.size(); i++) {
		auto obj = parsedGO[i];
		int parentIndex = obj.parentId;
		auto x = addGameObject(obj.name);
		auto transformCmp = x->addComponent<TransformCmp>();
		std::shared_ptr<Body2DCmp> bodyCmp = nullptr;
		std::shared_ptr<SpriteRendererCmp> spriteCmp = nullptr;

		//TransformCmp set up
		transformCmp->position = obj.position;
		transformCmp->rotation = obj.rotationEuler;
		transformCmp->scale = obj.scale;

		if (parentIndex != -1) {
			auto parentObj = this->getGameObject(parentIndex).get();
			parentObj->getComponent<TransformCmp>()->childs.push_back(x);
			x->getComponent<TransformCmp>()->parent = parentObj;
		}
		//Body2DCmp set up
		if (obj.bodyShape != "") {
			bodyCmp = x->addComponent<Body2DCmp>();
			if (obj.bodyShape == "box") {
				bodyCmp->setUp(RandomShape2DType::Box, obj.bodyType);
			}
			else if (obj.bodyShape == "circle") {
				bodyCmp->setUp(RandomShape2DType::Circle, obj.bodyType);
			}
		}
		//SpriteRendererCmp set up
		if (obj.spriteNameInAtlas != "") {
			spriteCmp = x->addComponent<SpriteRendererCmp>();
			spriteCmp->setUp(RandomEngine::spriteAtlas->getSprite(obj.spriteNameInAtlas), RandomEngine::spriteDefaultMat, obj.spriteColor, obj.spriteScale);
		}
	}
};