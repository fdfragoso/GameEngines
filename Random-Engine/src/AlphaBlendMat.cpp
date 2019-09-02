#include "AlphaBlendMat.hpp"
#include "AlphaChannelShader.hpp"
#include "SRE/Texture.hpp"
#include <SRE/Shader.hpp>
using namespace SRE;

AlphaBlendMat::AlphaBlendMat(){
	auto i = new AlphaChannelShader();
	shader = i->shader;
	defaultTex = SRE::Texture::getWhiteTexture();
}


void AlphaBlendMat::buildMat(SRE::Texture * tex) {
	shader->set("tex", tex);
}
