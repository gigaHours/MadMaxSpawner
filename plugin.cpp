#include "plugin.h"

DLLATTATCH;

#include <intrin.h>
#pragma intrinsic(_ReturnAddress)

void PluginAttach(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
}



void PluginHooks() {
	//HookMgr::Install(ADDRESS(0x140492B70, 0x1420A2960), HookMgr::RETFALSE); // CSaveManager::CanAutoSave
	//HookMgr::MakeRET(ADDRESS(0x1404CF0B0, 0x1420E82F0)); // CSaveManager::HandleEvent - skip CSaveManager::SaveSlot(this, this->m_AutoSaveSlot);
}