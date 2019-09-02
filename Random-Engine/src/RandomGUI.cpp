//
// Created by Random Engine on 10/11/16.
//

#include "RandomGUI.hpp"
#include "RandomEngine.hpp"
#include "RandomInterpolation.hpp"
//Profiler
#include "Profiler.hpp"

using namespace std;

Profiler profiler;

Scene * RandomGUI::currentScene = nullptr;

void RandomGUI::startRandomGUI(SDL_Window* window) {
	this->window = window;
	//Initializing IMGUI
	ImGui_SRE_Init(window);
}

void RandomGUI::setScene(Scene * newScene) {
	currentScene = newScene;
}

void RandomGUI::update(){
	ImGui_SRE_NewFrame(window);

	if (showDebugGUI) {
		drawDebugGUI();
	}

	for (int i = 0; i < currentScene->getSize(); i++) {
		auto & go = currentScene->getGameObject(i);
		go->showGUI();
	}
	ImGui::Render();
}

void RandomGUI::drawDebugGUI() {
	ImGui::SetNextWindowSize(ImVec2(450, 200), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("RandomEngine Debug Window", &showDebugGUI);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//Quit button
	if (ImGui::Button("Quit App", {100,20})) {
		RandomEngine::quitGameLoop();
	}
	//Memory Usage Control Panel
	if (ImGui::CollapsingHeader("Memory usage")) {
		float frecuency = 2;
		const int memVecSize = 50;
		static float virtualVec[memVecSize] = { 0 };
		static float physicalVec[memVecSize] = { 0 };
		static int index = 0;
		SIZE_T currentVirtualMem = profiler.getVirtualMemUse();
		SIZE_T currentPhysicalMem = profiler.getPhysicalMemUse();
		static float refresh_time = ImGui::GetTime();
		for (; ImGui::GetTime() > refresh_time + 1.0f / frecuency; refresh_time += 1.0f / frecuency) {
			currentVirtualMem = profiler.getVirtualMemUse();
			currentPhysicalMem = profiler.getPhysicalMemUse();
			virtualVec[index] = currentVirtualMem;
			physicalVec[index] = currentPhysicalMem;
			index = (index + 1) % memVecSize;
		}
		ImGui::Columns(2, NULL, false);
		ImGui::BulletText("Virual Memory Used:");
		ImGui::NextColumn();
		ImGui::Text("%d", currentVirtualMem);
		ImGui::SameLine();
		ImGui::Text("Kbs");
		ImGui::NextColumn();
		ImGui::TextColored(ImVec4(0.7f, 0, 0.7f, 1.0f), "Max Virtual Memory");
		ImGui::NextColumn();
		ImGui::Text("%d", profiler.maxVirtualMem);
		ImGui::SameLine();
		ImGui::Text("Kbs");
		ImGui::NextColumn();
		ImGui::BulletText("Physical Memory Used:");
		ImGui::NextColumn();
		ImGui::Text("%d", currentPhysicalMem);
		ImGui::SameLine();
		ImGui::Text("Kbs");
		ImGui::NextColumn();
		ImGui::TextColored(ImVec4(0.7f, 0, 0.7f, 1.0f), "Max Physical Memory");
		ImGui::NextColumn();
		ImGui::Text("%d", profiler.maxPhysicalMem);
		ImGui::SameLine();
		ImGui::Text("Kbs");
		ImGui::Columns(1);
		ImGui::PlotLines("", virtualVec, memVecSize, index, "Virtual Memory", 0, profiler.maxVirtualMem, ImVec2(300, 100));
		ImGui::PlotLines("", physicalVec, memVecSize, index, "Physical Memory", 0, profiler.maxPhysicalMem, ImVec2(300, 100));
	}
	//Game Objects Tree Graph
	if (ImGui::CollapsingHeader("GameObjects Features")) {
		ImGui::Checkbox("Debug Draw - Physics2D", &(RandomEngine::physicsDebugMode));
		for (int i = 0; i<currentScene->getSize(); i++) {
			auto gameObject = currentScene->getGameObject(i);
			auto transform = gameObject->getComponent<TransformCmp>();
			auto particle = gameObject->getComponent<ParticleEmitterCmp>();
			if (transform->parent == nullptr) {
				if (ImGui::TreeNode(gameObject->getName().c_str())) {
					ImGui::Checkbox("Visible", &(gameObject->visible));
					ImGui::DragFloat3("position", &(transform->position.x));
					ImGui::DragFloat3("rotation", &(transform->rotation.x));
					ImGui::DragFloat3("scale", &(transform->scale.x));

					if (particle != nullptr) {
						ImGui::DragFloat("Velocity", &(particle->guiVelocity));
						particle->setVelocity(glm::vec3(glm::circularRand(particle->guiVelocity), 0.0));

						static float colMin[4] = { particle->minColor.r, particle->minColor.g, particle->minColor.b, particle->minColor.a };
						static float colMax[4] = { particle->maxColor.r, particle->maxColor.g, particle->maxColor.b, particle->maxColor.a };
						static int iT;
						ImGui::ColorEdit4("Min Color", colMin);
						ImGui::ColorEdit4("Max Color", colMax);
						ImGui::Combo("Combo", &iT, "Random\0Linear\0Bezier");
						particle->setColor({ colMin[0],colMin[1],colMin[2],colMin[3] },
						{ colMax[0],colMax[1],colMax[2],colMax[3] },
							InterpolationType(iT));
						}
					drawGameObjChildsTree(transform);
					ImGui::TreePop();
				}
			}
		}
	}
	ImGui::End();
}

void RandomGUI::drawGameObjChildsTree(std::shared_ptr<TransformCmp> transform) {
	if (transform->childs.size() == 0) {
		return;
	}
	for (int i = 0; i < transform->childs.size(); i++) {
		auto gameObject = transform->childs[i];
		auto transform = gameObject->getComponent<TransformCmp>();
		if (ImGui::TreeNode(gameObject->getName().c_str())) {
			ImGui::Checkbox("Visible", &(gameObject->visible));
			ImGui::DragFloat3("position", &(transform->position.x));
			ImGui::DragFloat3("rotation", &(transform->rotation.x));
			ImGui::DragFloat3("scale", &(transform->scale.x));
			drawGameObjChildsTree(transform);
			ImGui::TreePop();
		}
	}
}

void RandomGUI::shutDown() {
	ImGui_SRE_Shutdown();
	currentScene = nullptr;
	delete currentScene;
}

void RandomGUI::handleEvent(SDL_Event * event) {
	ImGui_SRE_ProcessEvent(event);
}
