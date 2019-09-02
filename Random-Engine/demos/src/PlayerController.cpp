//Needed header
#include "PlayerController.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"
#include "SceneManager.hpp"

#include <iostream>

using namespace SRE;

PlayerController::PlayerController(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void PlayerController::Start() {
	jumpImpulse = 1300;
	score = 0;
	canJump = true;
	gameOver = false;
}

void PlayerController::Update(float dt) {
	if (gameOver) {
		if (RandomInput::getKeyDown(SDLK_SPACE)) {
			SceneManager::loadScene(5);
		}
		return;
	}
	score += dt;
	if (canJump && RandomInput::getKeyDown(SDLK_w)) {
		auto myBody = gameObject->getComponent<Body2DCmp>()->myBody;
		float impulse = myBody->GetMass() * jumpImpulse;
		myBody->ApplyForceToCenter({ 0, impulse }, true);
		gameObject->getComponent<AnimationCmp>()->setAnim("jump");
		canJump = false;
	}
	
}

void PlayerController::OnGUI() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize({200, 100 }, ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Demo1", false, window_flags);
	ImGui::SetWindowPos({ 0,0 }, 0);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.3);
	ImGui::Text("Random Engine - Random Game");
	ImGui::Text("Controls");
	ImGui::Text("W : Jump");
	ImGui::End();

	if (!gameOver) {
		ImGui::SetNextWindowSize({300, 100 }, ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Game Panel", false, window_flags);
		ImGui::SetWindowPos({ 0, 100 }, 0);
		ImGui::Value("Score", score);
		ImGui::End();
	} else {
		ImGui::SetNextWindowSize({ 350, 150 }, ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Gameover", false, window_flags);
		ImGui::SetWindowPos({ (RandomEngine::width/2)-100, (RandomEngine::height / 2)-100 }, 0);
		ImGui::Text("GAME OVER");
		ImGui::Text("Random Game by:");
		ImGui::Text("Atanas Slavov");
		ImGui::Text("Felipe Fragoso");
		ImGui::Text("Sergio Valderrama");
		ImGui::Text("Special thanks to Iver Quispe!!");
		ImGui::Value("Final Score", score);
		if (ImGui::Button("Try Again (SPACE)", { 150,20 })) {
			SceneManager::loadScene(5);
		}
		if (ImGui::Button("Quit App", { 100,20 })) {
			RandomEngine::quitGameLoop();
		}
		ImGui::End();
	}
}

void PlayerController::OnCollisionEnter(GameObject * other) {
	auto name = other->getName();
	if (name == "groundC") {
		canJump = true;
		if (!gameOver) {
			gameObject->getComponent<AnimationCmp>()->setAnim("run");
		}
	} else if (name == "foxOnBike" || name == "car1" || name == "car2") {
		setGameOver();
	}
}

void PlayerController::OnCollisionExit(GameObject * other) {
}

void PlayerController::setGameOver() {
	gameObject->getComponent<AnimationCmp>()->setAnim("jump");
	gameOver = true;
}