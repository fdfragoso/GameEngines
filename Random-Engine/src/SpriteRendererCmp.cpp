#include "SpriteRendererCmp.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
using namespace SRE;

SpriteRendererCmp::SpriteRendererCmp(GameObject *gameObject)
	:Component(gameObject)
{
}


SpriteRendererCmp::~SpriteRendererCmp()
{
}
//SpriteDefaultMat * mat
void SpriteRendererCmp::setUp(Sprite* sprite, SpriteDefaultMat * mat, glm::vec4 color, glm::vec3 scale) {
	this->sprite = sprite;
	this->mat = mat;
	this->color = color;
	this->scale = scale;
}

void SpriteRendererCmp::render(glm::mat4 globalTransform) {
	mat->buildMat(sprite->texture);
	//mat->buildMat(sprite->texture, color);
	SimpleRenderEngine::instance->draw(sprite->mesh, glm::scale(globalTransform, scale) , mat->shader);
}
