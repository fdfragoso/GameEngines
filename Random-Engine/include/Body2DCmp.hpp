
#pragma once

#include "Box2D/Box2D.h"
#include <SRE/Mesh.hpp>
#include "glm/glm.hpp"
#include "Component.hpp"
#include "RandomPhysics2D.hpp"


//! Body2DCmp
/*! Inherits from component class */
/*! Creates a body for a game object, with a shape and bodytype */

class Body2DCmp : public Component {
public:
	/*! Creates a body2d with the desired shape and type */
	/*! Position, rotation and scale are taken from TransformCmp */
	/**
	* @param {RandomShape2DType} shapeType - Can be: Box and Circle
	* @param {b2BodyType} bodyType - Can be: Static, Kinematic, and Dynamic
	*/
	void setUp(RandomShape2DType shapeType, b2BodyType bodyType);
	/**
	* Body2D component destructor
	*/
	~Body2DCmp();
	b2Body* myBody;
protected:
	/**
	* Body2D Component constructor - Inherits from Compontn
	* @param {GameObject *} gameObject - The game object that this component belongs to
	*/
	Body2DCmp(GameObject *gameObject);
	friend class GameObject;
};


