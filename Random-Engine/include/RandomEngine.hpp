
//!Random Engine
/*! */
/*! RandomEngine is a 2D game engine based on SRE */
/*! We have some useful classes that can help the developer to make a 2D game */
/*! We only support top level Body2DCmp */
/*! adding this component to any game object children can cause malfunctioning */
/*! Created by: */
/*! Atanas Slavov */
/*! Felipe Dacal Fragoso */
/*! Sergio Javier Valderrama Vidaurre */
/*! \Version $Revision: 0.1 $ */

#pragma once
//Useful definitions
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define DEG_TO_RAD (M_PI/180)
#define RAD_TO_DEG (180/M_PI)

//SRE and SDL
#include "SDL.h"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Texture.hpp"
#include <SRE/Shader.hpp>
//Components
#include "TransformCmp.hpp"
#include "MeshCmp.hpp"
#include "Body2DCmp.hpp"
#include "SpriteRendererCmp.hpp"
#include "ParticleEmitterCmp.hpp"
#include "ScriptableCmp.hpp"
#include "AnimationCmp.hpp"
//Random Physics
#include "RandomPhysics2D.hpp"
//Random GUI
#include "RandomGUI.hpp"
//Random Input
#include "RandomInput.hpp"
//Random Materials
#include "DefaultRandomMat.hpp"
#include "SpriteDefaultMat.hpp"
#include "ParticleRandomMat.hpp"
//Sprite Atlas
#include "SpriteAtlas.hpp"

class Scene;

class RandomEngine {
public:
	/**
	* Random Engine constructor
	* @param {SDL_Window *} window - Window created by SDL
	* @param {int} width - The desired window width
	* @param {int} height - The desired window height
	* @param {bool} debugMode - Enables physicsDebugMode and access to the debug GUI (by pressing R)
	**/
    RandomEngine(SDL_Window* window, float width, float height, bool debugMode);
	/**
	* Random Engine desductor
	**/
    virtual ~RandomEngine();
	/**
	* Starts the game loop until 'quit' is true
	**/
    void startGameLoop();
	/**
	* Handles SDL events and passes the event to ImGUI
	**/
	void HandleSDLEvents();
	/**
	* Sets the new scene as the current scene
	* @param {Scene *} newScene - The new scene
	**/
	static void setScene(Scene * newScene);
	/**
	* Sets 'quit' to false so Random Engine can stop the game loop
	**/
	static void quitGameLoop();
	/**
	* Pointer to our own particle material, used to render particles
	**/
	static ParticleRandomMat * particleMat;
	/**
	* Pointer to our own default material, used to render 3D meshes
	**/
	static DefaultRandomMat * defaultMat;
	/**
	* Pointer to our own sprite default material, used to render sprites
	**/
	static SpriteDefaultMat * spriteDefaultMat;
	/**
	* Pointer to our sprite atlas, where you can store sprites
	**/
	static SpriteAtlas * spriteAtlas;
	/**
	* The current scene that Random Engine is running
	**/
	static Scene * currentScene;
	/**
	* Vector that stores the game objects that will be destroyed at the start of the next frame
	**/
	static std::vector<GameObject * > toDestroy;
	static bool quit;
	static bool physicsDebugMode;
	static bool pauseEngine;
	static float deltaTimeSec;
	static float width;
	static float height;

private:
	/**
	* Creates the engine default materials: particle and sprite materials
	**/
	void createDefaultMaterials();
	bool debugMode;
	SRE::Mesh* quadMesh;
	SRE::Mesh* sphereMesh;
	SRE::Mesh* cubeMesh;
	
	SDL_Window* window;
	DebugDraw * debugDrawInstance;

	RandomPhysics2D randomPhysics2D;
	RandomGUI randomGUI;
	RandomInput randomInput;

	SRE::SimpleRenderEngine * sre;
};

