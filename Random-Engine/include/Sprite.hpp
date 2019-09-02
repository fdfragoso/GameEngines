#pragma once

#include "glm/glm.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Texture.hpp"
#include "SRE/SimpleRenderEngine.hpp"


//! Sprite
/**
* Create a sprite and set it's properties
*/
class Sprite {
public:
	/**
	* Sprite construnctor
	* @param {int} x - The starting X coordinate of the texture from which we will create the sprite
	* @param {int} y - The starting Y coordinate of the texture from which we will create the sprite
	* @param {int} width - The width that we will take from the texture
	* @param {int} height - The height that we will take from the texture
	* @param {float} anchorX - The x value of the anchor point that will be used when drawing , from 0 to 1
	* @param {float} anchorY - The y value of the anchor point that will be used when drawing , from 0 to 1
	**/
    Sprite(int x, int y, int width, int height, float anchorX, float anchorY, SRE::Texture * texture);
    /**
	* Sprite destructor
	* Delete the sprite
	*/
	virtual ~Sprite();
	SRE::Mesh* mesh;
	SRE::Texture* texture;
};

