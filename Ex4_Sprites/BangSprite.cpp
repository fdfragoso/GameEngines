#include "BangSprite.h"

BangSprite::BangSprite(const sre::Sprite & sprite, glm::vec2 _position) : GameObject(sprite)
{
	position = _position;
	scale = glm::vec2(0.7f, 0.7f);
}
