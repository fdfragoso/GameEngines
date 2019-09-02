#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Component.hpp"

#include "glm/glm.hpp"
class Scene;

//! GameObject
/*! One of the most important classes of Random Engine */
/*! A GameObject has a name and belongs to a scene */
/*! Contains all the necessary functions to work with all components */

class GameObject {
public:
	/**
	* GameObject deconstructor
	*/
    ~GameObject();
	/**
	* Returns the GameObject name
	* @return {string}
	*/
    std::string getName();
	/**
	* Template that supports the addition of components
	* @return {shared_ptr<Component>} - Returns the component that was added
	*/
    template<typename C>
    std::shared_ptr<C> addComponent();
	/**
	* Finds and removes the desired component
	* @param {shared+ptr<Component>} ptr - The component to be deleted
	* @return {bool} - True if deletion was successful
	*/
    bool removeComponent(std::shared_ptr<Component> ptr);
	/**
	* Returns the component required
	* @return {shared_ptr<Component>}
	*/
    template<typename C>
    std::shared_ptr<C> getComponent();
	/**
	* Renders particles and sprites based on the components
	*/
	void draw();
	/**
	* Updates the transform of the GameObject based on the transform of its body
	*/
	void updateGlobalTransform();
	/**
	* Updates the transform of the collider based on the transform of GameObject
	*/
	void updateCollider();
	/**
	* Calls Start() on all Scriptable components
	*/
	void scriptStart();
	/**
	* Calls Update() on all Scriptable components
	* @param {float} dt - Delta time 
	*/
	void scriptUpdate(float dt);
	/**
	* Calls OnGUI() on all Scriptable components
	*/
	void showGUI();
	bool visible = true;

private:
    std::vector<std::shared_ptr<Component>> components;
	/**
	* GameObject constructor
	* @param {string} name 
	*/
    GameObject(std::string name);
    std::string name;
    friend class Scene;
};

template<typename C>
std::shared_ptr<C> GameObject::addComponent() {
    C * c = new C(this);
    auto res = std::shared_ptr<C>(c);
    components.push_back(res);
    return res;
}

template<typename C>
std::shared_ptr<C> GameObject::getComponent() {
    for (auto c : components){
        auto castPtr = std::dynamic_pointer_cast<C>(c);
        if (castPtr != nullptr){
            return castPtr;
        }
    }
    return nullptr;
}



