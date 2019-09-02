
#pragma once

class GameObject;

//!Component
/**
* Base class that is the parent of all components
*/
class Component {
public:
    virtual ~Component();
	/**
	* Returns the game object that this component belongs to
	* @returns {GameObject*}
	*/
    GameObject* getGameObject();
protected:
	/**
	* Component constructor
	* @param {GameObject*} - The game object that this component belongs to
	*/
    Component(GameObject *gameObject);
	GameObject *gameObject;

    friend class GameObject;
};


