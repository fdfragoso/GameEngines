#include "LeakDetector.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"

//Random Engine!
#include "RandomEngine.hpp"
#include "SceneManager.hpp"
//Custom Scenes
#include "Demo01.hpp"
#include "Demo02.hpp"
#include "Demo03.hpp"
#include "Demo032.hpp"
#include "Demo04.hpp"
#include "GameScene.hpp"

using namespace std;

int main(int argc, char** argv) {
	markPoint();
	int aux;
	std::cout << "Random Engine demos & game\n1 - Sprites, Animations and Alpha Blend Shader\n2 - RandomPhysics2D\n3, 4 - Scene Manager\n5 - Particle System\n6 - Game" << std::endl;
	std::cin >> aux;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    int width = 640;
    int height = 480;
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "Your game name",                  // game title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            width,                               // width, in pixels
            height,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully made
    if (window == NULL) {
        //Show error
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
	//Initializing Random Engine!
	RandomEngine randomEngine(window, width, height, true);
	//Add your scenes here
	SceneManager::addScene(new Demo01());
	SceneManager::addScene(new Demo02());
	SceneManager::addScene(new Demo03());
	SceneManager::addScene(new Demo032());
	SceneManager::addScene(new Demo04());
	SceneManager::addScene(new GameScene());
	//If it is the game, then disable physicsDebugMode
	if (aux == 6) {
		randomEngine.physicsDebugMode = false;
	}
	//Load one scene
		SceneManager::loadScene(aux - 1);

	//Start game!
	randomEngine.startGameLoop();

    // Close and destroy the window
    SDL_DestroyWindow(window);
    // Clean up
    SDL_Quit();
	randomEngine.~RandomEngine();
	checkLeaks();
	int x;
	std::cin >> x;
    return 0;
}