
#include <ctime>
#include <glm/gtc/constants.hpp>
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.h"
#include "LaserShot.h"
#include "BangSprite.h"
#include <string>
#include <iostream>

using namespace sre;

AsteroidsGame::AsteroidsGame() {
    r.setWindowTitle("Asteroids");
    r.init(SDL_INIT_EVERYTHING,       // Create the window and the graphics context (instantiates the sre::Renderer). Note that most
           SDL_WINDOW_OPENGL          
           );

    time_t t;                                               // random value based on time
    srand((unsigned) time(&t));

	score = 0;
    atlas = SpriteAtlas::create("asteroids.json","asteroids.png");
    gameObjects.push_back(std::make_shared<SpaceShip>(atlas->get("playerShip1_orange.png"), this));
	spawnInitialObject();
	gameOver = false;

    camera.setWindowCoordinates();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };

    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}

void AsteroidsGame::SpawnLaser(glm::vec2 _position, float _rotation ,glm::vec2 _velocity)
{
	auto laserSprite = atlas->get("laserRed01.png");
	gameObjects.push_back(std::make_shared<LaserShot>(laserSprite, _position, _velocity, _rotation, this));
}

void AsteroidsGame::DeleteObject(GameObject* objectToDelete)
{
	int objectIndex;
	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i].get() == objectToDelete) 
		{
			objectIndex = i;
		}
	}
	//delete gameObjects[objectIndex].get();
	gameObjects.erase(gameObjects.begin()+objectIndex);
}

void AsteroidsGame::SpawnAsteroid(AsteroidSize _currentSize, glm::vec2 _currentPos)
{
	switch (_currentSize)
	{
	case Small:
		break;
	case Medium:
		gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_small1.png"), 14, _currentPos, this, Small));
		gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_small1.png"), 14, _currentPos, this, Small));
		break;
	case Big:
		gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_med1.png"), 22, _currentPos, this, Medium));
		gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_med1.png"), 22, _currentPos, this, Medium));
		break;
	default:
		break;
	}
}

void AsteroidsGame::SpawnBang(glm::vec2 _currentPos)
{
	gameObjects.push_back(std::make_shared<BangSprite>(atlas->get("bang.png"), _currentPos));
	gameOver = true;
}

void AsteroidsGame::ResetGame()
{
	//for (int i = 0; i < gameObjects.size(); i++) 
	//{
	//	DeleteObject(gameObjects[i].get());
	//}
	//TODO implement game reset
	score = 0;
	gameObjects.clear();
	gameObjects.push_back(std::make_shared<SpaceShip>(atlas->get("playerShip1_orange.png"), this));
	spawnInitialObject();
}

void AsteroidsGame::IncreaseScore()
{
	score++;
}

void AsteroidsGame::spawnInitialObject()
{
	//Spawn asteroids
	for (int j = 0; j < 5; j++) 
	{
		gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_big3.png"), 40, this, Big));
	}
	for (int i = 0; i < 5; i++) 
	{
		
		int output = (rand() % static_cast<int>(2));
		switch (output)
		{
		case 0:
			gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_small1.png"), 14, this, Small));
			break;
		case 1:
			gameObjects.push_back(std::make_shared<Asteroid>(atlas->get("meteorBrown_med1.png"), 22, this, Medium));
			break;
		default:
			break;
		}
		
	}
}

void AsteroidsGame::update(float deltaTime) {
	for (int i = 0; i < gameObjects.size(); i++) 
	{
		Collidable * col1 = dynamic_cast<Collidable*>(gameObjects[i].get());
		if(col1 == NULL)
		{
			continue;
		}

		for (int j = i+1; j < gameObjects.size(); j++) 
		{
			Collidable * col2 = dynamic_cast<Collidable*>(gameObjects[j].get());
			if (col2 == NULL)
			{
				continue;
			}
			CollidableType col1Type = col1->GetColType();
			CollidableType col2Type = col2->GetColType();
			float distance = glm::distance(gameObjects[i]->position, gameObjects[j]->position);
			if (distance <= (col1->getRadius() + col2->getRadius()) )
			{
				col1->onCollision(gameObjects[j], col2Type);
				col2->onCollision(gameObjects[i], col1Type);
			}
		}
	}
	for (int i = 0; i < gameObjects.size();i++) {
		
		gameObjects[i]->update(deltaTime);
    }
}

void drawCircle(std::vector<glm::vec3>& lines, glm::vec2 position, float radius){
    float quaterPi = glm::quarter_pi<float>();
    for (float f = 0;f<glm::two_pi<float>();f += quaterPi){
        // line from
        lines.push_back(glm::vec3{position.x + cosf(f)*radius,
                                  position.y + sinf(f)*radius,
                                  0
        });
        // line to
        lines.push_back(glm::vec3{position.x + cosf(f+quaterPi)*radius,
                                  position.y + sinf(f+quaterPi)*radius,
                                  0
        });
    }
}

void AsteroidsGame::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {0, 0, 0, 1})
            .build();
    auto spriteBatchBuilder = SpriteBatch::create();
    for (auto & go : gameObjects){
        go->render(spriteBatchBuilder);
    }
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);

    if (debugCollisionCircles){
        std::vector<glm::vec3> lines;
        for (auto & go : gameObjects){
            auto col = dynamic_cast<Collidable*>(go.get());
            if (col != nullptr){
                drawCircle(lines, go->position, col->getRadius());
            }
        }
        renderPass.drawLines(lines);
    }
	ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x / 2 - 100, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(200, 70), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::LabelText("GOs", "%i", gameObjects.size());
	ImGui::LabelText("Score", "%i", score);
	ImGui::End();
}

void AsteroidsGame::keyEvent(SDL_Event &event) {
	//for (auto & go : gameObjects) {
	for (int i = 0; i < gameObjects.size();i++) {
			gameObjects[i]->onKey(event);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
        debugCollisionCircles = !debugCollisionCircles;
    }
	if (event.key.keysym.sym == SDLK_SPACE)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (gameOver)
			{
				ResetGame();
				gameOver = false;
			}
		}
	}
}

int main(){
    new AsteroidsGame();
    return 0;
}