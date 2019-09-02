//Needed header
#include "Demo3C2.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"
#include "SceneManager.hpp"

#include <iostream>


using namespace SRE;

Demo3C2::Demo3C2(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void Demo3C2::Start() {
}

void Demo3C2::Update(float dt) {
	if (RandomInput::getKeyDown(SDLK_a)) {
		SceneManager::loadScene(2);
	}
}

void Demo3C2::OnGUI() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize({(float)RandomEngine::width, (float)RandomEngine::height }, ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Demo3", false, window_flags);
	ImGui::SetWindowPos({ 0,0 }, 0);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.3);
	ImGui::Text("Random Engine Tech Demo 03");
	ImGui::Text("SceneManager - This is scene 03");
	ImGui::Text("Press R to open debug window and look into Memory Usage");
	ImGui::Value("Gameobjects in scene", RandomEngine::currentScene->getSize());
	ImGui::Text("A: Go back to scene 2");
	if (ImGui::Button("Quit App", { 100,20 })) {
		RandomEngine::quitGameLoop();
	}
	ImGui::End();
}

void Demo3C2::OnCollisionEnter(GameObject * other) {
}

void Demo3C2::OnCollisionExit(GameObject * other) {
}