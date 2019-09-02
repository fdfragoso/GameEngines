#include "DefaultRandomMat.hpp"

#include "SRE/Texture.hpp"
#include <SRE/Shader.hpp>

using namespace SRE;

DefaultRandomMat::DefaultRandomMat(){
	shader = SRE::Shader::getStandard();
	defaultTex = SRE::Texture::getWhiteTexture();
	defaultColor = glm::vec4(1, 1, 1, 1);
}

DefaultRandomMat::~DefaultRandomMat() {
	delete defaultTex;
	delete shader;
}

void DefaultRandomMat::buildMat() {
	shader->set("tex", defaultTex);
	shader->set("color", defaultColor);
}

void DefaultRandomMat::buildMat(SRE::Texture * tex) {
	shader->set("tex", tex);
	shader->set("color", defaultColor);
}

void DefaultRandomMat::buildMat(glm::vec4 color){
	shader->set("tex", defaultTex);
	shader->set("color", color);
}

void DefaultRandomMat::buildMat(SRE::Texture * tex, glm::vec4 color){
	shader->set("tex", tex);
	shader->set("color", color);
}
