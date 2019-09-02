#include "MeshCmp.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace SRE;

MeshCmp::MeshCmp(GameObject *gameObject)
	:Component(gameObject)
{
}


MeshCmp::~MeshCmp()
{
}

void MeshCmp::setUp(Mesh *mesh, DefaultRandomMat * myMat, glm::vec4 color) {
	this->mesh = mesh;
	this->myMat = myMat;
	this->color = color;
}

void MeshCmp::render(glm::mat4 globalTransform) {
	myMat->buildMat(color);
	SimpleRenderEngine::instance->draw(mesh, globalTransform, myMat->shader);
}
