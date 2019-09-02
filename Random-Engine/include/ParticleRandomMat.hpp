#pragma once

#include "RandomMaterial.hpp"


//! ParticleRandomMat
/**
* Particle material class, inheriting from RandomMaterial
*/
class ParticleRandomMat : public RandomMaterial{
public:

	/*! ParticleRandomMat constructor */
	/*! assigns default values for the shader and texture */ 
	ParticleRandomMat();
	
	/*! ParticleRandomMat destructor */
	/*! deletes shader and texture */
	~ParticleRandomMat();
	/**
	* Assigns the default texture to the shader
	*/
	void buildMat() override;
	/**
	* Assigns a custom texture to the shader
	* @param {SRE::Texture *} tex - pointer to custom texture
	*/
	void buildMat(SRE::Texture *tex) override;
};


