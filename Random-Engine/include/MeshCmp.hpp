#pragma once

#include <SRE/Mesh.hpp>
#include "glm/glm.hpp"
#include "Component.hpp"
#include "DefaultRandomMat.hpp"

//! MeshCmp
/*! Class that inherits from Component class */
/*! Used to create mesh for 3D GameObjects */

class MeshCmp : public Component {
public:
	~MeshCmp();
	
	/*! Setup function */
	/*! Assigns the passed mesh, material and color to the component */
	/**
	* @param {SRE::Mesh *} mesh - pointer to the mesh
	* @param {RandomEngine::DefaultRandomMat *} myMat - pointer to the material
	* @param {glm::vec4} color - vector for RGBA color values
	*/

	void setUp(SRE::Mesh* mesh, DefaultRandomMat * myMat, glm::vec4 color);
	/**
	* Renders the mesh using SRE's draw function
	* @param {glm::mat4} globalTransform - the global Transform of the parent
	*/
	void render(glm::mat4 globalTransform);
	glm::vec4 color;
private:
    SRE::Mesh* mesh;
	DefaultRandomMat * myMat;
protected:
	/**
	* Mesh Component constructor - inherits from Component
	* @param {GameObject *} gameObject - The game object that this component belongs to
	*/
	MeshCmp(GameObject *gameObject);
	friend class GameObject;
};


