#include "Ball.hpp"

#include "sre/Mesh.hpp"
#include "sre/Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "sre/Renderer.hpp"
#include <time.h>

using namespace sre;
using namespace glm;

Ball::Ball() {
	
	position = glm::vec2(0);
    radius = 10;
}

void Ball::draw(sre::RenderPass& renderPass) {
    renderPass.draw(mesh, getTransform(), material);
}

void Ball::move(float deltaTimeInSeconds) {
	position += velocity*deltaTimeInSeconds;
    // Todo exercise 2
}

glm::mat4 Ball::getTransform() {
    // Todo exercise 1
	glm::vec3 scaleV = glm::vec3(7.5f, 7.5f, 0.1f);
	glm::mat4 scaleM = glm::scale(scaleV);
	glm::vec3 translV = glm::vec3(position.x, position.y, 0.1f);
	glm::mat4 translM = glm::translate(translV);
    return translM * scaleM;
}

void Ball::init() {

	srand(static_cast <unsigned> (time(0)));

	glm::vec2 screeSize = sre::Renderer::instance->getWindowSize();
	position = glm::vec2(screeSize.x / 2.0f, screeSize.y / 2.0f);

    mesh = Mesh::create().withSphere().build();
    auto shader = Shader::getUnlit();
    material = shader->createMaterial();
    material->setColor(vec4(1));
}
