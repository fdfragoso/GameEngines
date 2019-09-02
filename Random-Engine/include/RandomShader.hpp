#pragma once

#include "SRE/Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL\glew.h"

using namespace SRE;
//! RandomShader
/**
* Parent class for our custom shaders to inherit from
*/
class RandomShader {
public:
	virtual ~RandomShader();
	SRE::Shader* shader;
protected:
	const char* vertexShader;
	const char* fragmentShader;
};