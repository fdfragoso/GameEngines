#pragma once

#include "SRE/ParticleMesh.hpp"
#include "glm/glm.hpp"
#include <vector>
#include "Component.hpp"
#include "ParticleRandomMat.hpp"

#include "RandomInterpolation.hpp"

//! Particle
/*! Helper class for ParticleEmitterCmp */
/*! Used to create a map of particles */

class Particle {
public:
	/**
	* Particle constructor
	* @param {glm::vec3} position - position of the particle in x, y, z
	* @param {glm::vec3} velocity - velocity of the particle in x, y, z
	* @param {float} timeOfBirth - time of birth of the particle
	* @param {glm::vec4} color - RGBA colors of the particle. Each color is a floating point value with a range from 0 to 1
	* @param {float} size - size of the particle
	*/
	Particle(glm::vec3 position, glm::vec3 velocity, float timeOfBirth, glm::vec4 color, float size);
	glm::vec4 color;
	glm::vec3 position;
	glm::vec3 velocity;
	float size;
	float timeOfBirth;
};


//! ParticleEmitterCmp
/*! Inherits from Component class */
/*! Has functions to set up and update a particle emitter */

class ParticleEmitterCmp : public Component {
public:
	
	/*! ParticleEmitterCmp destructor */
	/*! Clears the particles map and calls delete on the texture and mesh pointers */
	
	~ParticleEmitterCmp();
	/*! Setup function for the particle system emitter */
	/*! Populates the particles map with Particle objects */
	/*! Also populates the finalPos, sizes, colors, uvs, uvSize and uvRotation maps, used in the update() function */
	/**
	* @param {int} size - number of particles to be made for the particles map
	* @param {SRE::Texture *} - the texture that the particles will have
	*/
	void setUp(int size, SRE::Texture * myTex);
	/**
	* Emit a particle
	* @param {glm::vec3} position - position of the particle
	* @param {glm::vec3} velocity - velocity of the particle
	*/
	void emit(glm::vec3 position, glm::vec3 velocity);
	
	/*! Updates the particles in the map */
	/*! Updates position, color and size of each particle */
	
	void update();
	/**
	* Assigns a material and draws the particles on screen
	*/
	void render();

	/**
	* Sets a static color to the particle
	* @param {glm::vec4} color - RGBA colors of the particle. Each color is a floating point value with a range from 0 to 1
	*/
	void setColor(glm::vec4 color);
	/**
	* Sets a minimum and maximum range for the color of the particle, and a type of interpolation to be used to interpolate between them
	* @param {glm::vec4} minColor - RGBA values for the minimum color of the particle
	* @param {glm::vec4} maxColor - RGBA values for the maximum color of the particle
	* @param {RandomInterpolation::InterpolationType} i - type of interpolation used
	*/
	void setColor(glm::vec4 minColor, glm::vec4 maxColor, InterpolationType i);
	/**
	* Gets the current color of the particle
	* @return {glm::vec4}
	*/
	glm::vec4 getColor();
	/**
	* Sets a velocity for the particle
	* @param {glm::vec3} velocity - velocity of the particle in x, y, z axis
	*/
	void setVelocity(glm::vec3 velocity);
	/**
	* Gets the current velocity of the particle
	* @return {glm::vec4}
	*/
	glm::vec3 getVelocity();

	//Colors
	glm::vec4 minColor = { 1,1,1,1 };
	glm::vec4 maxColor;

	//Velocity
	glm::vec3 staticVelocity = { 0,0,0 };
	float guiVelocity = 0;
private:
	const float gravity = -9.8f;
	float currentTime;
	int emissionIndex;
	ParticleRandomMat * particleMat;
	SRE::ParticleMesh* mesh;
	SRE::Texture * myTex;
	//Color properties
	bool isSolidColor = true;
	InterpolationType interpolationType;


	std::vector<glm::vec3> finalPos;
	std::vector<Particle> particles;
	std::vector<glm::vec4> colors;
	std::vector<float> sizes;
	std::vector<float> uvSize;
	std::vector<float> uvRotation;
	std::vector<glm::vec2> uvs;
protected:
	/**
	* ParticleEmpitter Component constructor - inherits from Component
	* @param {GameObject *} gameObject - The game object that this component belongs to
	*/
	ParticleEmitterCmp(GameObject *gameObject);
	friend class GameObject;
};


