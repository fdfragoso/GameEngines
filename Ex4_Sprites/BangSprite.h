#pragma once

#include "GameObject.hpp"
#include "AsteroidsGame.hpp"

class BangSprite : public GameObject {
public:
	BangSprite(const sre::Sprite &sprite, glm::vec2 _position);
private:
};