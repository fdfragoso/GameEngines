
#pragma once

#include <map>
#include <vector>
#include "glm/glm.hpp"
#include "Component.hpp"
#include "Sprite.hpp"

#include <time.h>


//!Animation
/**
* Stores a sprite sequence that is played in a defined duration
*/
class Animation {
public:
	/**
	* Animation constructor
	* @param {vector<Sprite*>} sprites - The sprite sequence
	* @param {float} durationMs - The total sequence duration in ms
	*/
	Animation(std::vector<Sprite*> sprites, float durationMs);
	std::vector<Sprite*> sprites;
	float durationMs;
	float minTime;
};

/*! Animation Component */
/*! Inherits from Component class */
/*! Contains multiple animations, and can switch between them */
/*! Also you can play, stop, pause the current animation */


class AnimationCmp : public Component {
public:
	
	/*! AnimationCmp destructor */
	/*! Clears all the animations */
	
	~AnimationCmp();
	/**
	* Stores the new animation in the animations map
	* @param {string} sprites - The new animation name
	* @param {float} durationMs - The new animation
	*/
	void createAnim(std::string name, Animation * anim);
	/**
	* Plays the desired animation
	* @param {string} name - The desired animation
	*/
	void setAnim(std::string name);
	/**
	* Plays the current animation
	*/
	void play();
	/*
	* Stops the current animation
	*/
	void stop();
	/**
	* Pauses the current animation
	*/
	void pause();
	/**
	* Modifies the current animation total duration
	* @param {float} duration - The new duration
	*/
	void setCurrentAnimDuration(float duration);
	/**
	* Returns the current animation total duration
	* @return {float}
	*/
	float getCurrentAnimDuration();
	/**
	* Returns the sprites that needs to be rendered
	* @return {Sprite *}
	*/
	Sprite* getCurrentSprite();
private:
	int currentIndex;
	bool resetAnim;
	bool isPlaying;
	clock_t clockInit;
	std::string currentAnimName;
    std::map<std::string, Animation*> animations;
protected:
	/**
	* Animation Component constructor - inherits from Component
	* @param {GameObject *} gameObject - The game object that this component belongs to
	*/
	AnimationCmp(GameObject *gameObject);
	friend class GameObject;
};


