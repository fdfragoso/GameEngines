#include "SpriteDefaultMat.hpp"

#include "SRE/Texture.hpp"
#include <SRE/Shader.hpp>

using namespace SRE;

SpriteDefaultMat::SpriteDefaultMat(){
	shader = SRE::Shader::getUnlitSprite();
	defaultTex = SRE::Texture::getWhiteTexture();
	defaultColor = glm::vec4(1, 1, 1, 1);
}

SpriteDefaultMat::~SpriteDefaultMat() {
	//white texture gets deleted in DefaultRandomMat
	delete shader;
}

void SpriteDefaultMat::buildMat() {
	shader->set("tex", defaultTex);
	shader->set("color", defaultColor);
}

void SpriteDefaultMat::buildMat(SRE::Texture * tex) {
	shader->set("tex", tex);
	shader->set("color", defaultColor);
}

void SpriteDefaultMat::buildMat(glm::vec4 color) {
	shader->set("tex", defaultTex);
	shader->set("color", color);
}

void SpriteDefaultMat::buildMat(SRE::Texture * tex, glm::vec4 color) {
	shader->set("tex", tex);
	shader->set("color", color);
}