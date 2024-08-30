#include "plugin.h"
#include "vendor/imgui.h"

DLLATTATCH;

void PluginAttach(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
}


void PluginHooks() {
	ImGuiRenderer::Install();
}