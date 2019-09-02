#pragma once

#include "glm/glm.hpp"

#include "sre/Material.hpp"
#include "sre/Shader.hpp"
#include "sre/RenderPass.hpp"

class Ball {
public:
    Ball();
    void init();
    void draw(sre::RenderPass& renderPass);

    void move(float deltaTimeInSeconds);

    glm::vec2 position;
    float radius;

    glm::vec2 velocity; // pixels per seconds
private:
    glm::mat4 getTransform();
    std::shared_ptr<sre::Material> material;
    std::shared_ptr<sre::Mesh> mesh;
};


