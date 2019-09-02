#pragma once

#include "SDL.h"
#include "SRE/SimpleRenderEngine.hpp"

#include "Box2D/Box2D.h"
#include "DebugDraw.h"

class b2Draw;

/*! RandomShape2DType */
/*! Enum class with RandomEngine's supported collider shapes */
enum RandomShape2DType {
	Box,
	Circle
};


//!Random Physics 2D
/**
* Controls the 2D physics in the world game
*/
class RandomPhysics2D : public b2ContactListener {
public:
	/**
	* Start physics 2D component in the world
	*/
	void startRandomPhysics2D();
	/**
	* Stop physics 2D component in the world
	*/
	void stopRandomPhysics2D();
	static b2World* world;
	//Collisions callbacks
	/**
	* Collision callback when contact begins
	* @param {b2Contact *} contact - 
	*/
	virtual void BeginContact(b2Contact* contact);
	/**
	* Collision callback when contact ends
	* @param {b2Contact *} contact -
	*/
	virtual void EndContact(b2Contact* contact);
private:
	DebugDraw * debugDrawInstance;

};

