#include "Collidable.hpp"

float Collidable::getRadius() const {
    return radius;
}

void Collidable::setRadius(float radius) {
    Collidable::radius = radius;
}

CollidableType Collidable::GetColType()
{
	return _myType;
}
