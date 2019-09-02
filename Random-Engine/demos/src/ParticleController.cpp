//Needed header
#include "ParticleController.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"

#include <iostream>


using namespace SRE;

ParticleController::ParticleController(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void ParticleController::Start() {
}

void ParticleController::Update(float dt) {
	//gameObject->getComponent<ParticleEmitterCmp>()->setVelocity(glm::vec3(glm::circularRand(15.0f), 0.0));
}

void ParticleController::OnGUI() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize({(float)RandomEngine::width, (float)RandomEngine::height }, ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Demo4", false, window_flags);
	ImGui::SetWindowPos({ 0,0 }, 0);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.3);
	ImGui::Text("Random Engine Tech Demo 04");
	ImGui::Text("Particle systems");
	ImGui::Text("Press R to open debug window");
	ImGui::Text("Look under Particles for options:");
	ImGui::Text("We have Velocity, Color and Interpolation modification");
	if (ImGui::Button("Quit App", { 100,20 })) {
		RandomEngine::quitGameLoop();
	}
	ImGui::End();
}
