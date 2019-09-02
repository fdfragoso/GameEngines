#pragma once

#include "RandomMaterial.hpp"

//!DefaultRandomMat
/**
* Material class, inheriting from RandomMaterial
*/
class DefaultRandomMat : public RandomMaterial{
public:
	
	/*! DefaultRandomMat constructor */
	/*! assigns default values for the shader, texture and color */
	DefaultRandomMat();
	/*! DefaultRandomMat destructor */
	/*! deletes shader and texture */
	~DefaultRandomMat();
	/**
	* Assigns the default texture and color to the shader
	*/
	void buildMat() override;
	/**
	* Assigns a custom texture and default color to the shader
	* @param {SRE::Texture *} tex - pointer to custom texture
	*/
	void buildMat(SRE::Texture *tex) override;
	/**
	* Assigns a custom color and default texture to the shader
	* @param {glm::vec4} color -  vector for RGBA color values
	*/
	void buildMat(glm::vec4 color) override;
	/**
	* Assigns a custom color and custom texture to the shader 
	* @param {SRE::Texture *} tex - pointer to custom texture
	* @param {glm::vec4} color -  vector for RGBA color values
	*/
	void buildMat(SRE::Texture *tex, glm::vec4 color) override;
};


