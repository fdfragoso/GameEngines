#include "Component.hpp"


Component::Component(GameObject *gameObject)
:gameObject(gameObject)
{
}

Component::~Component() {
}

GameObject *Component::getGameObject() {
    return gameObject;
}