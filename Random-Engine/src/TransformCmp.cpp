#include "TransformCmp.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.hpp"

#include <iostream>

using namespace SRE;

TransformCmp::TransformCmp(GameObject *gameObject)
	:Component(gameObject)
{
	
}

glm::mat4 TransformCmp::localTransform() {
	glm::mat4 rZ = glm::eulerAngleZ(glm::radians(rotation.z));
	glm::mat4 rY = glm::eulerAngleY(glm::radians(rotation.y));
	glm::mat4 rX = glm::eulerAngleX(glm::radians(rotation.x));
	glm::mat4 newTranslate = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, position.z));
	return glm::scale(newTranslate * rZ * rY * rX, scale);
}

glm::mat4 TransformCmp::globalTransform() {
	if (parent != nullptr) {
		return parent->getComponent<TransformCmp>()->globalTransform() * localTransform();
	}
    return localTransform();
}

void TransformCmp::setPosition(glm::vec3 newPos) {
	position = newPos;
}

void TransformCmp::setRotation(glm::vec3 newRot) {
	rotation = newRot;
}

glm::vec3 TransformCmp::getGlobalPosition() {
	glm::mat4 transform = globalTransform();
	return glm::vec3(transform[3].x, transform[3].y, transform[3].z);
}

glm::vec3 TransformCmp::getGlobalRotation() {
	return rotation;
	/*glm::mat4 transform = globalTransform();
	auto matrix = glm::value_ptr(transform);
	float ry = glm::asin(matrix[2]);
	float rx = 0;
	float rz = 0;
	if (ry < M_PI/2) {
		if (ry > -M_PI / 2) {
			rx = glm::atan(-matrix[6] / matrix[10]);
			rz = glm::atan(-matrix[1] / matrix[0]);
		} else if (ry <= -M_PI / 2) {
			rx = -glm::atan(matrix[6] / matrix[10]);
			rz = 0;
		}
	} else {
		rx = glm::atan(matrix[6] / matrix[10]);
		rz = 0;
	}
	return glm::vec3(rx *180 / M_PI, ry * 180 / M_PI, -rz * 180 / M_PI);
	*/
}