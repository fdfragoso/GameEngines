#pragma once

#include <sre/RenderPass.hpp>
#include "sre/Mesh.hpp"
#include "sre/Material.hpp"
#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace sre;
using namespace glm;

struct Edge2D{
    glm::vec2 from;
    glm::vec2 to;
    glm::vec2 normal;
};

class Box {
public:
    Box();
    void init();
    void draw(sre::RenderPass& renderPass);

    // get the 2D edge, with the edge normal (perpendicular to the edge)
    Edge2D getEdge(int index);

    glm::vec2 position;
    glm::vec2 scale;
private:
    glm::mat4 getTransform();
    std::shared_ptr<sre::Material> material;
    std::shared_ptr<sre::Mesh> mesh;
};


