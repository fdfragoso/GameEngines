//Needed header
#include "MarioController.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"
#include "SceneManager.hpp"

#include <iostream>

using namespace SRE;

MarioController::MarioController(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void MarioController::Start() {
	movVel = 2;
	rotVel = 40;
	animSpeedRate = 100;
}

void MarioController::Update(float dt) {
	auto transform = gameObject->getComponent<TransformCmp>();
	auto anim = gameObject->getComponent<AnimationCmp>();
	if (RandomInput::getKey(SDLK_d)) {
		transform->position.x += movVel * dt;
		anim->setAnim("walk");
	} else if (RandomInput::getKey(SDLK_a)) {
		transform->position.x -= movVel * dt;
		anim->setAnim("walk");
	} else if (RandomInput::getKey(SDLK_w)) {
		transform->rotation.z += rotVel * dt;
		anim->setAnim("jump");
	}else {
		anim->setAnim("idle");
	}

	if (RandomInput::getKey(SDLK_q)) {
		anim->setCurrentAnimDuration(anim->getCurrentAnimDuration() + animSpeedRate);
	} else  if (RandomInput::getKey(SDLK_e)) {
		anim->setCurrentAnimDuration(anim->getCurrentAnimDuration() - animSpeedRate);
	}
	
}

void MarioController::OnGUI() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize({(float)RandomEngine::width, (float)RandomEngine::height }, ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Demo1", false, window_flags);
	ImGui::SetWindowPos({ 0,0 }, 0);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.3);
	ImGui::Text("Random Engine Tech Demo 01");
	ImGui::Text("Mario Controls");
	ImGui::Text("A - D : Move");
	ImGui::Text("W : Rotate");
	ImGui::Text("E : Hold To Increase Current Animation Speed");
	ImGui::Text("Q : Hold To Decrease Current Animation Speed");
	if (ImGui::Button("Quit App", { 100,20 })) {
		RandomEngine::quitGameLoop();
	}
	ImGui::End();
}

void MarioController::OnCollisionEnter(GameObject * other) {
}

void MarioController::OnCollisionExit(GameObject * other) {
}