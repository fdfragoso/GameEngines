#include "SideScrollingCamera.hpp"
#include "BirdGame.hpp"

using namespace glm;

SideScrollingCamera::SideScrollingCamera(GameObject *gameObject)
        : Component(gameObject)
{
    camera.setOrthographicProjection(BirdGame::windowSize.y/2,-1,1);
}

sre::Camera &SideScrollingCamera::getCamera() {
    return camera;
}

void SideScrollingCamera::update(float deltaTime) {
    auto position = followObject->getPosition();

    position.x += offset.x;
    position.y = offset.y;

    gameObject->setPosition(position);
    vec3 eye (position, 0);
    vec3 at (position, -1);
    vec3 up (0, 1, 0);
    camera.lookAt(eye, at, up);
}

void SideScrollingCamera::setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset) {
    this->followObject = followObject;
    this->offset = offset;
}
