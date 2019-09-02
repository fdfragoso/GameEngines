//Needed header
#include "SpamController.hpp"
#include "RandomEngine.hpp"
//Optional headers
#include "RandomGUI.hpp"

#include <iostream>


using namespace SRE;

SpamController::SpamController(GameObject * gameobject) : ScriptableCmp(gameobject) {
}

void SpamController::Start() {
	nPlants = 0;
}

void SpamController::Update(float dt) {
	if (RandomInput::getKey(SDLK_a)) {
		spamPlant();
	} else  if (RandomInput::getKey(SDLK_d)) {
		auto plant = RandomEngine::currentScene->getGameObject("plant");
		if (plant != nullptr) {
			nPlants--;
			RandomEngine::currentScene->removeGameObject(plant);
		}
	}
	
}

void SpamController::OnGUI() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize({(float)RandomEngine::width, (float)RandomEngine::height }, ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Demo2", false, window_flags);
	ImGui::SetWindowPos({ 0,0 }, 0);
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.3);
	ImGui::Text("Random Engine Tech Demo 02");
	ImGui::Text("Spam plants");
	ImGui::Text("A: Create plant");
	ImGui::Text("D : Destroy plant");
	ImGui::Value("Plants in scene", nPlants);
	if (ImGui::Button("Quit App", { 100,20 })) {
		RandomEngine::quitGameLoop();
	}
	ImGui::End();
}

void SpamController::OnCollisionEnter(GameObject * other) {
}

void SpamController::OnCollisionExit(GameObject * other) {
}

void SpamController::spamPlant() {
	Sprite * plantSprite = RandomEngine::spriteAtlas->getSprite("green_plant_0");
	auto plant = RandomEngine::currentScene->addGameObject("plant");
	auto transformCmp = plant->addComponent<TransformCmp>();
	transformCmp->setPosition({ 25,6,0 });
	transformCmp->setRotation({ 0,0,-10 });
	auto spriteCmp = plant->addComponent<SpriteRendererCmp>();
	spriteCmp->setUp(plantSprite, RandomEngine::spriteDefaultMat, { 1,1,1,1 }, { 0.07,0.07,1 });

	auto bodyCmp = plant->addComponent<Body2DCmp>();
	bodyCmp->setUp(RandomShape2DType::Box, b2BodyType::b2_dynamicBody);
	bodyCmp->myBody->SetFixedRotation(false);
	bodyCmp->myBody->SetLinearVelocity({ -7,12 });
	bodyCmp->myBody->SetAngularVelocity(1);

	nPlants++;
}