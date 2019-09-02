#pragma once

#include <string>
#include <map>
#include <SRE/SimpleRenderEngine.hpp>
#include "SRE/Texture.hpp"
#include "Sprite.hpp"


//! SpriteAtlas
/**
* Creates the sprite atlas from an image and json file
*/
class SpriteAtlas {
public:
	/**
	* Sprite Atlas constructor
	*/
    SpriteAtlas();
	/**
	* Sprite Atlas destructor
	* Clears all sprites from atlas and deletes the texture with sprites
	*/
	~SpriteAtlas();
	/**
	* Create the sprite atlas from json file
	* @param {string} atlasJsonPath - The path from json file
	* @param {string} fileName - The name of json file
	*/
	void addFromFile(std::string atlasJsonPath, std::string fileName);
	/*
	* Clear the sprite atlas
	**/
	void clearAtlas();
	/**
	* Returns the sprite by name
	* @param {string} name - Sprite name
	* @return {Sprite *}
	*/
    Sprite* getSprite(std::string name);
private:
    std::map<std::string, Sprite*> sprites;
	SRE::Texture* texture;
};


