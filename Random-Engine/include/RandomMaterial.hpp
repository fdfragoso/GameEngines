#pragma once

#include "SRE/Texture.hpp"
#include <SRE/Shader.hpp>

//!RandomMaterial
/**
* Base class for materials that all other materials inherit from
*/
class RandomMaterial{
public:
	virtual ~RandomMaterial();
	/**
	* Virtual function for building a material with default values
	*
	*/
	virtual void buildMat();
	/**
	* Virtual function for building a material with custom texture
	* @param {SRE::Texture *} tex - pointer to texture
	*/
	virtual void buildMat(SRE::Texture *tex);
	/**
	* Virtual function for building a material with custom color
	* @param {glm::vec4} color -  vector for RGBA color values
	*/
	virtual void buildMat(glm::vec4 color);
	/**
	* Virtual function for building a material with custom texture and color
	* @param {SRE::Texture *} tex - pointer to texture
	* @param {glm::vec4} color -  vector for RGBA color values
	*/
	virtual void buildMat(SRE::Texture *tex, glm::vec4 color);
	SRE::Shader* shader;
protected:
	SRE::Texture *defaultTex;
	glm::vec4 defaultColor;
};


