#pragma comment(lib, "d3d11.lib")

//#include <mm/core/graphicsengine/graphicsengine.h>
#include "mm/graphicsengine.h"
#include "imgui_detour_dx11.h"
#include "hookmgr.h"

ImGui::DetourDX11::present  ImGui::DetourDX11::p_present = 0;
ImGui::DetourDX11::present	ImGui::DetourDX11::p_present_target = 0;

WNDPROC ImGui::DetourDX11::oWndProc = 0;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall ImGui::DetourDX11::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void ImGui::DetourDX11::DetourPresent(IDXGISwapChain* m_SwapChain, ID3D11Device* m_D3DDevice)
{
}

void (*Graphics__Flip_orig)(Graphics::HDevice_t* device);
void Graphics__Flip_hook(Graphics::HDevice_t* device) {

	if (device->m_Context->m_Mutex)
		EnterCriticalSection((LPCRITICAL_SECTION)device->m_Context->m_Mutex);



	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	
	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (device->m_Context->m_Mutex)
		LeaveCriticalSection((LPCRITICAL_SECTION)device->m_Context->m_Mutex);

	return Graphics__Flip_orig(device);
}

void (*DestroyRenderSetups_orig)(NGraphicsEngine::CGraphicsEngine* thiz);
void DestroyRenderSetups_hook(NGraphicsEngine::CGraphicsEngine* thiz) {

	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();

	return DestroyRenderSetups_orig(thiz);
}

void(*CreateRenderSetups_orig)(NGraphicsEngine::CGraphicsEngine* thiz);
void CreateRenderSetups_hook(NGraphicsEngine::CGraphicsEngine* thiz) {

	CreateRenderSetups_orig(thiz);

	static bool init1 = false;
	static bool init2 = false;

	DXGI_SWAP_CHAIN_DESC sd;
	thiz->m_GraphicsDevice->m_SwapChain->GetDesc(&sd);

	if (!init1) {

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui::DetourDX11::oWndProc = (WNDPROC)SetWindowLongPtr(sd.OutputWindow, GWLP_WNDPROC, (LONG_PTR)ImGui::DetourDX11::WndProc);
		init1 = true;
	}

	
	ImGui_ImplWin32_Init(sd.OutputWindow);
	ImGui_ImplDX11_Init(thiz->m_GraphicsDevice->m_D3DDevice, thiz->m_GraphicsDevice->m_Context->m_Context);
}

void ImGui::DetourDX11::Install(uintptr_t flipAddr, uintptr_t createRender, uintptr_t destroyRender)
{
	//GetPresentPointer();

	HookMgr::Install(flipAddr, Graphics__Flip_hook, Graphics__Flip_orig);
	HookMgr::Install(createRender, CreateRenderSetups_hook, CreateRenderSetups_orig);
	HookMgr::Install(destroyRender, DestroyRenderSetups_hook, DestroyRenderSetups_orig);
}