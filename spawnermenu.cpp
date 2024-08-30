#include "plugin.h"
#include "mm/imgui/imgui.h"

#include "mm/core/avasingle.h"
#include "mm/core/graphics/graphicsengine.h"
#include "mm/core/input.h"

class ImGuiSpawnerMenu : public ImGuiRenderer {
public:
	ImGuiSpawnerMenu() : ImGuiRenderer() {

	}

	void Game() override {

	}

	void GameHandleEvent(Event const& _event) override {
		if (_event.hash == HASHSTR("focus")) {
			CAvaSingle<CDeviceManager>::Instance->GetInputManager()->SetInFocus(!_event.Arg<bool>(0));
			CAvaSingle<NGraphicsEngine::CGraphicsEngine>::Instance->SetCursor(_event.Arg<bool>(0) ? 0 : -1);
		}
	};

	bool show = false;
	void Render() override {

		if (ImGui::IsKeyJustDown(ImGuiKey_Slash)) {
			show = !show;
			SendGameEvent(Event("focus").Add(show));
		}

		if (!show)
			return;

		ImGui::Begin("Spawner");
		
		ImGui::End();
	}
};

ImGuiSpawnerMenu spawnerMenu;