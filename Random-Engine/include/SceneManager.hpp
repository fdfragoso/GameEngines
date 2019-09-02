#pragma once

#include <vector>
//Components
#include "Scene.hpp"


//! Scene Manager
/**
* Manage all scenes and their dependencies
*/
class SceneManager {
public:
	/**
	* Add new scene
	* @param {Scene *} newScene - Scene to be add
	*/
	static void addScene(Scene *newScene);
	/**
	* Load a scene
	* @param {int} index - INdex of the scne to be load
	*/
	static void loadScene(int index);
	
	/*! Load resources from the scene */
	/*! This is supposed to be called after load scene */
	
	static void loadResources();
	/**
	* Delete all scenes
	*/
	static void deleteAllScenes();
	static int currentIndex;
	static bool haveToLoad;

private:
	static std::vector<Scene *> scenes;
	static Scene * currentScene;
};

