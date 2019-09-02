#include "Box.hpp"
#include "sre/Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "sre/Renderer.hpp"

using namespace sre;
using namespace glm;

Box::Box() {
    position = vec2(0,0);
    scale = vec2(1,1);
}

void Box::draw(sre::RenderPass& renderPass) {
    renderPass.draw(mesh, getTransform(), material);
}

glm::mat4 Box::getTransform() {

	glm::mat4 scaleM = glm::scale(glm::vec3(scale,0.1f));
	glm::mat4 translM = glm::translate(glm::vec3(position, 0.1f));
	return translM * scaleM;
}

Edge2D Box::getEdge(int index) {
    Edge2D res;
    glm::vec4 vertices[] = {
            glm::vec4(-1,-1,0,1),
            glm::vec4(1,-1,0,1),
            glm::vec4(1,1,0,1),
            glm::vec4(-1,1,0,1),
    };
    res.from = vec2(getTransform() * vertices[index]);
    res.to = vec2(getTransform() * vertices[(index+1)%4]);
    vec2 norm = normalize(res.to - res.from);
    res.normal = vec2(norm.y,-norm.x);

    return res;
}

void Box::init() {
    mesh = Mesh::create().withCube().build();
    auto shader = Shader::getUnlit();
    material = shader->createMaterial();
    material->setColor(vec4(1));
}
