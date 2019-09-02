#include "ParticleRandomMat.hpp"

#include "SRE/Texture.hpp"
#include <SRE/Shader.hpp>

using namespace SRE;

ParticleRandomMat::ParticleRandomMat(){
	shader = SRE::Shader::getStandardParticles();
	defaultTex = SRE::Texture::getSphereTexture();
}

ParticleRandomMat::~ParticleRandomMat() {
	delete defaultTex;
	delete shader;
}

void ParticleRandomMat::buildMat() {
	shader->set("tex", defaultTex);
}

void ParticleRandomMat::buildMat(SRE::Texture * tex) {
	shader->set("tex", tex);
}