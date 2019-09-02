#pragma once

#include <vector>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class GameObject;

enum AsteroidSize { Small, Medium, Big };

class AsteroidsGame {
public:
    AsteroidsGame();
	void SpawnLaser(glm::vec2 _position, float _rotation ,glm::vec2 _velocity);
	void DeleteObject(GameObject* objectToDelete);
	void SpawnAsteroid(AsteroidSize _currentSize, glm::vec2 _currentPos);
	void SpawnBang(glm::vec2 _currentPos);
	void ResetGame();
	void IncreaseScore();

private:
    void update(float deltaTime);
    void render();
    void keyEvent(SDL_Event &event);
	void spawnInitialObject();

    sre::Camera camera;
    sre::SDLRenderer r;
    std::shared_ptr<sre::SpriteAtlas> atlas;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	int score;
    bool debugCollisionCircles = false;
	bool gameOver;
};


