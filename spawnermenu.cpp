#include "plugin.h"
#include "mm/imgui/imgui.h"

class ImGuiSpawnerMenu : public ImGuiRenderer {
public:
	ImGuiSpawnerMenu() : ImGuiRenderer() {

	}

	void Game() override {

	}

	void Render() override {

		ImGui::Begin("Spawner");
		if (ImGui::Button("Test"))
			SendGameEvent([]() { Log("This game event!"); });
		ImGui::End();
	}
};

ImGuiSpawnerMenu spawnerMenu;