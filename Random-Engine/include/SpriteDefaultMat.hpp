#pragma once

#include "RandomMaterial.hpp"

//! SpriteDefaultMat
/*! Inherits from RandomMaterial class. */
/*! Build the materials for sprites in scene. */ 

class SpriteDefaultMat : public RandomMaterial{
public:
	
	/*! SpriteDefaultMat constructor */
	/*! Creates a new default material for sprite */
	
	SpriteDefaultMat();
	
	/*! SpriteDefaultMat destructor */
	/*! Clears the default material from sprite */
	
	~SpriteDefaultMat();
	/**
	* Sets the default material with default texture and color
	*/
	void buildMat() override;
	/**
	* Sets the material with a given texture and a default color
	* @param {SRE::Texture *} tex - pointer to the texture 
	*/
	void buildMat(SRE::Texture *tex) override;
	/**
	* Sets the material with the default texture and a given color
	* @param {glm::vec4} color - Representation of RGBA colors. Each color is a floating point value with a range from 0 to 1
	*/
	void buildMat(glm::vec4 color) override;
	/**
	* Sets the material with a given texture and color
	* @param {SRE::Texture *} tex - pointer to the texture 
	* @param {glm::vec4} color - Representation of RGBA colors. Each color is a floating point value with a range from 0 to 1
	*/
	void buildMat(SRE::Texture *tex, glm::vec4 color) override;
};


