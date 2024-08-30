#include "plugin.h"
#include "mm/imgui/imgui.h"

DLLATTATCH;

void PluginAttach(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
}


void PluginHooks() {
	ImGuiRenderer::Install();
	HookMgr::Patch(ADDRESS(0x1403DB400, 0x141FD4D0C), "\xFF", 1); // veh spawn limit
	HookMgr::Patch(ADDRESS(0x1403DB402, 0x141FD4D0E), "\xFF", 1); // ch spawn limit
	HookMgr::MakeNOP(ADDRESS(0x1405CD1C5, 0x142203AEB), 7); // always Vehicle lockedForPlayer = false
}