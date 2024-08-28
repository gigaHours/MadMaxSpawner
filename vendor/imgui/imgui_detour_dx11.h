#pragma once

#include <d3d11.h>
#include "../imgui.h"

namespace ImGui
{	
	class DetourDX11
	{
	public:
		static void Install(uintptr_t flipAddr, uintptr_t createRender, uintptr_t destroyRender);

		static void AddToInit(void(*func)());
		static void AddToRender(void(*func)());
		static void AddToPreRender(void(*func)());
		static void RemoveFromRender(void(*func)());

		typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);

		static bool GetPresentPointer();
		static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static void DetourPresent(IDXGISwapChain* m_SwapChain, ID3D11Device* m_D3DDevice);

		static present p_present, p_present_target;
		static WNDPROC oWndProc;
	};
}
