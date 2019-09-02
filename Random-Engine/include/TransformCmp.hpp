#pragma once
#include <memory>
#include <vector>
#include <SRE/Mesh.hpp>
#include "glm/glm.hpp"
#include "Component.hpp"
class GameObject;


//! TransformCmp
/*! Inherits from Component class. */
/*! Contains position, rotation and scale of a gameObject. */
/*! Also you can set a local and global transform properties. */
class TransformCmp : public Component {
public:
    glm::vec4 color;
    glm::vec3 position = { 0,0,0 };
    glm::vec3 rotation = { 0,0,0 };
    glm::vec3 scale = { 1,1,1 };

	/**
	* Returns the local transform of a gameObject in the scene
	*/
    glm::mat4 localTransform();
    
	/**
	* Returns the global transform of a gameObject in the scene
	*/
	glm::mat4 globalTransform();

	/**
	* Modifies the current position of a certain gameObject  
	* @param {glm::vec3} newPos - The new position
	*/
	void setPosition(glm::vec3 newPos);
	
	/**
	* Modifies the current rotation of a certain gameObject
	* @param {glm::vec3} newRot - The new rotation
	*/
	void setRotation(glm::vec3 newRot);
	
	/**
	* Returns the global position of a gameObject in the scene
	*/
	glm::vec3 getGlobalPosition();
	
	/**
	* Returns the global rotation of a gameObject in the scene
	*/
	glm::vec3 getGlobalRotation();

	GameObject * parent = nullptr;
	std::vector<std::shared_ptr<GameObject>> childs;
protected:

	/**
	* Transform Component constructor - inherits from Component
	* @param {GameObject *} gameObject - The game object that this component belongs to 
	*/
	TransformCmp(GameObject *gameObject);
	friend class GameObject;
};


