#pragma once
#include <memory>
#include <vector>
#include <SRE/Mesh.hpp>
#include "glm/glm.hpp"
#include "Component.hpp"
class GameObject;


//! ScriptableCmp
/**
*  Class containing virtual functions to be overwritten in child scripts inheriting from ScriptableCmp
*/
class ScriptableCmp : public Component {
public:
	/*! Start function is only executed one time, in the first frame. */
	/*! Used to setup all needed variables and initialize functions used by the script. */
	virtual void Start();
	/*! Update function is called every frame. */
	/*! Update is the most commonly used function to implement any kind of game behaviour. */
	virtual void Update(float dt);
	/*! OnGUI is called every frame. */
	/*! OnGUI is used to build all the graphics user interface. */
	virtual void OnGUI();
	/*! OnCollisionEnter is called when this GameObject's collider has begun colliding with another. */
	virtual void OnCollisionEnter(GameObject * other);
	/*! OnCollisionExit is called when this GameObject's collider has stopped colliding another collider. */
	virtual void OnCollisionExit(GameObject * other);

protected:
	/**
	* Scriptable Component constructor
	* @param {GameObject *} gameObject - The game object that this component belongs to
	*/
	ScriptableCmp(GameObject *gameObject);
	friend class GameObject;
};


