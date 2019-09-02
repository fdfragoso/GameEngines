#pragma once

//IMGUI
#include <imgui.h>
#include "SRE/imgui_sre.hpp"
//Components
#include "TransformCmp.hpp"
#include "ParticleEmitterCmp.hpp"
#include "Scene.hpp"


//! RandomGUI
/**
* Creates the user interface
*/
class RandomGUI {
public:
	/**
	* Initialize the user interface
	* @param {SDL_Window *} window - The window to draw the user interface
	*/
	void startRandomGUI(SDL_Window* window);
	/**
	* Draw the user interface 
	*/
	void update();
	/**
	* Draw all the profiler information in the user interface 
	*/
	void drawDebugGUI();
	/**
	* Draw all the GameObjects in the Tree on screen
	* @param {std::shared_ptr<TransformCmp>} transform - The transform component of the GameObject
	*/
	void drawGameObjChildsTree(std::shared_ptr<TransformCmp> transform);
	bool showDebugGUI = false;
	/**
	* Clear the user interface and delete it
	*/
	void shutDown();
	/**
	* Draw the SDL event
	* @param {SDL_Event *} event - SDL Event that is happening
	*/
	void handleEvent(SDL_Event * event);
	/**
	* Set scene as the current one 
	* @param {Scene *} newScene - Scene to be set as current one
	*/
	static void setScene(Scene * newScene);

private:
	SDL_Window* window;
	static Scene * currentScene;

};

