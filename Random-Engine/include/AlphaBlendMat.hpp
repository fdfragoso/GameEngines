#pragma once

#include "SpriteDefaultMat.hpp"
#include "AlphaChannelShader.hpp"
//! AlphaBlendMat
/*! Inherits from DefaultRandomMat class. */
/*! Uses custom AlphaChannelShader for sprites in scene. */ 

class AlphaBlendMat : public SpriteDefaultMat {
public:
	/** 
	* AlphaBlendMat constructor
	* Creates a new alphablended material for sprite
	*/
	AlphaBlendMat();
	/**
	* Sets a given texture to the material
	* @param {SRE::Texture *} tex - pointer to the texture
	*/
	void buildMat(SRE::Texture *tex) override;
private:
	AlphaChannelShader *x;
};


