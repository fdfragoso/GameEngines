#pragma once

#include <string>
#include <vector>
#include "GameObject.hpp"


//! Scene
/**
* Manipulate the game objects in the scene.
*/
class Scene {
public:
	/**
	* Add game object to the scene
	* @param {string} name - Name of the game object to be added
	* @return {std::shared_ptr<GameObject>}
	*/
    std::shared_ptr<GameObject> addGameObject(std::string name);
	/**
	* Remove game object from the scene
	* @param {std::shared_ptr<GameObject>} ptr - Pointer of the game object to be destroyed
	* @return {bool}
	*/
    bool removeGameObject(std::shared_ptr<GameObject> ptr);
	/**
	* Get the number of game objects in the scene
	* @return {int}
	*/
    int getSize();
	/**
	* Get game object by index
	* @param {int} index - Index of game object to get
	* @return {std::shared_ptr<GameObject>}
	*/
    std::shared_ptr<GameObject> getGameObject(int index);
	/**
	* Get game object by name - returns the first one
	* @param {string} name - Name of game object to get
	* @return {std::shared_ptr<GameObject>}
	*/
	std::shared_ptr<GameObject> getGameObject(std::string name);
	/**
	* Returns all components of type C
	* @return {std::vector<std::shared_ptr<C>>}
	*/
    template<typename C>
    std::vector<std::shared_ptr<C>> getAllComponent();
	/**
	* Delete all game objects from the scene
	*/
	void removeAllGameObjects();
	/**
	* Add game objects from json file
	* @param {string} file - Name of Json file
	*/
	void addFromFile(std::string file);
	/**
	* Load all GameObjects
	*/
	virtual void load();

private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};

template<typename C>
std::vector<std::shared_ptr<C>> Scene::getAllComponent() {
    std::vector<std::shared_ptr<C>> res;
    for (auto& go :gameObjects){
        std::shared_ptr<C> c = go->getComponent<C>();
        if (c.get() != nullptr){
            res.push_back(c);
        }
    }
    return res;
}