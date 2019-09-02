#pragma once
#include "GameObject.hpp"

enum CollidableType { AsteroidCol, LaserCol, SpaceShipCol};

class Collidable {
public:
    virtual void onCollision(std::shared_ptr<GameObject> other, CollidableType colType) = 0;

    float getRadius() const;

    void setRadius(float radius);

	CollidableType GetColType();

protected:
	CollidableType _myType;
    float radius = 0;
};


