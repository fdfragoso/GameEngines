#include "Sprite.hpp"

#include "SRE/Shader.hpp"
#include "SRE/Mesh.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace SRE;

/**
* Sprite construnctor
* @param {int} x - The starting X coordinate of the texture from which we will create the sprite
* @param {int} y - The starting Y coordinate of the texture from which we will create the sprite
* @param {int} width - The width that we will take from the texture
* @param {int} height - The height that we will take from the texture
* @param {float} anchorX - The x value of the anchor point that will be used when drawing , from 0 to 1
* @param {float} anchorY - The y value of the anchor point that will be used when drawing , from 0 to 1
**/
Sprite::Sprite(int x, int y, int width, int height, float anchorX, float anchorY, SRE::Texture * myTexture) {
	texture = myTexture;

	int textureW = myTexture->getWidth();
	int textureH = myTexture->getHeight();
	float vx0 = (float)x / textureW;
	float vx1 = (float)(x + width) / textureW;
	float vy0 = (float)y / textureH;
	float vy1 = (float)(y + height) / textureH;

	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> vertices({
		glm::vec3{ width*(1 - anchorX),  height*-anchorY, 0 }, glm::vec3{ width*(1 - anchorX), height*(1 - anchorY), 0 },glm::vec3{ width*-anchorX, height*-anchorY, 0 },
		glm::vec3{ width*-anchorX, height*-anchorY, 0 }, glm::vec3{ width*(1 - anchorX), height*(1 - anchorY), 0 }, glm::vec3{ width*-anchorX, height*(1 - anchorY), 0 }
	});

	std::vector<glm::vec2> uvs({
		glm::vec2{ vx1, vy0 }, glm::vec2{ vx1, vy1 }, glm::vec2{ vx0, vy0 },
		glm::vec2{ vx0, vy0 }, glm::vec2{ vx1, vy1 }, glm::vec2{ vx0, vy1 }
	});
	mesh = new Mesh(vertices, normals, uvs);
}

Sprite::~Sprite() {
	delete mesh;
}