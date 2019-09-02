#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "SRE/Mesh.hpp"

#include "RandomPhysics2D.hpp"


//! GameObjectDescriptor
/*! Helper class for GameObjectParser */
/*! Consists of variables uniquely describing a game object */
/*! Variables include id, name, Transform, Box2D and sprite renderer properties */

class GameObjectDescriptor{
public:
    // Uniquely defines a game object
    int uniqueId;

	// Game object name
	std::string name;

	// Transform properties
	// position relative to parent
	glm::vec3 position;
	// rotation relative to parent
	glm::vec3 rotationEuler;
	// scale relative to parent
	glm::vec3 scale;
	// parent id (-1 means no parent)
	int parentId;

	//Body2D properties - if you dont want this component, leave bodyShape as empty string
    // body shape: "box", "circle"
    std::string bodyShape;
	// body 2D type: "static"(0), "kinematic"(1), "dynamic"(2)
	b2BodyType bodyType;
    
	//SpriteRenderer properties - if you dont want this component, leave spriteNameInAtlas as empty string
	// name of the sprite in the atlas
	std::string spriteNameInAtlas;
    // sprite color
    glm::vec4 spriteColor;
	// sprite scale
	glm::vec3 spriteScale;
    
};



//! GameObjectParser
/*! Parser class, used to parse .json files */
/*! Populates a vector of GameObjectDescriptor objects */
/**
* @param {string} filename - name of the file to parse
* @return {std::vector<GameObjectDescriptor>}
*/
class GameObjectParser{
public:
    static std::vector<GameObjectDescriptor> parseFile(std::string filename);
};
