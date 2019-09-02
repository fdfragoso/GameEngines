#pragma once

#include "sre/SDLRenderer.hpp"
#include "sre/Material.hpp"
#include "WorldMap.hpp"
#include "FirstPersonController.hpp"


class Wolf3D {
public:
    Wolf3D();
private:
    void init();
    void update(float deltaTime);
    void render();
    void addCube(std::vector<glm::vec3>& vertexPositions, std::vector<glm::vec4>& textureCoordinates, int x, int z, int type);
    void renderDebugBricks(sre::RenderPass & renderPass);
    sre::SDLRenderer r;
    sre::Camera camera;
    WorldMap map;
    std::shared_ptr<sre::Mesh> walls;

	//CEILING
	std::shared_ptr<sre::Mesh> ceiling;
	std::shared_ptr<sre::Material> ceilingMaterial;
	//END CEILING
	//FLOOR
	std::shared_ptr<sre::Mesh> floorMesh;
	std::shared_ptr<sre::Material> floorMaterial;
	//END FLOOR

    std::shared_ptr<sre::Material> wallMaterial;
    FirstPersonController fpsController;
    glm::vec4 floorColor;
    glm::vec4 ceilColor;
    bool debugBricks = false;
    bool lockRotation = false;

};

