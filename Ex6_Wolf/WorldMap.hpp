#pragma once

#include <vector>
#include <string>

#include "glm/glm.hpp"

class WorldMap {
public:
    void loadMap(std::string filename);
    int getTile(int x, int y);
    int getWidth();
    int getHeight();
    glm::vec2 getStartingPosition();
    float getStartingRotation();
    glm::vec4 getFloorColor();
    glm::vec4 getCeilColor();
private:
    std::vector<std::vector<int>> values;
    glm::vec2 startingPosition;
    float startingRotation;
    glm::vec4 floorColor;
    glm::vec4 ceilColor;
};


