#pragma once

#include <SRE/Mesh.hpp>
#include "glm/glm.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "SpriteDefaultMat.hpp"


//! SpriteRendererCmp
/*! Inherits from Component class. */
/*! Contains the sprite to be rendered in the scene. */

class SpriteRendererCmp : public Component {
public:

	/*!  Sprite Renderer destructor */
	/*!  Clear the renderer */
	
	~SpriteRendererCmp();
	/**
	* Set the Sprite to be rendered
	* @param {Sprite *} sprite - The sprite to be rendered
	* @param {SpriteDefaulMat *} mat - The default material used by the sprite
	* @param {glm::vec4} color - Representation of RGBA colors. Each color is a floating point value with a range from 0 to 1
	* @param {glm::vec3} scale - The scale of sprite to be rendered
	*/
	void setUp(Sprite* sprite, SpriteDefaultMat * mat, glm::vec4 color, glm::vec3 scale);
	/**
	* Draw the sprite on the scene
	* @param {glm::mat4} globalTransform - The global transform of the sprite to be rendered on the screen
	*/
	void render(glm::mat4 globalTransform);
	glm::vec4 color;
	glm::vec3 scale = { 1,1,1 };
private:
	SpriteDefaultMat * mat;
	Sprite * sprite;
protected:
	/**
	* Sprite Renderer Component construct - inherits from Component 
	* @param {GameObject *} gameObject - The game object that this component belongs to
	*/
	SpriteRendererCmp(GameObject *gameObject);
	friend class GameObject;
};


