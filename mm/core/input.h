#pragma once

#include "mm/std.h"
#include "mm/core/hash.h"

namespace Input {

	enum ELockedGamepadOrder : __int32
	{
		E_LOCKED_GAMEPAD_ORDER_NONE = -1,
		E_LOCKED_GAMEPAD_ORDER_1 = 0x0,
		E_LOCKED_GAMEPAD_ORDER_2 = 0x1,
		E_LOCKED_GAMEPAD_ORDER_3 = 0x2,
		E_LOCKED_GAMEPAD_ORDER_4 = 0x3,
		E_MAX_LOCKED_GAMEPADS = 0x4,
	};

	class CInputActionMap {
	public:

		/*float GetValue(CHashString const& action_hash) {
			return HookMgr::Call<float>(0x140927740, this, action_hash.m_Hash);
		}

		void SetEnabled(bool enabled) {
			return HookMgr::Call<void>(0x1409240F0, this, enabled);
		}*/
	};

	class IInputDeviceManager
	{
	public:

		uintptr_t* vtable;
		char _unk[104];

		/*CInputActionMap* GetActionMap(CHashString const& id) {
			return HookMgr::Call<CInputActionMap*>(0x140924140, this, &id);
		}

		CInputActionMap* CreateActionMap(CHashString const& id, int size, ELockedGamepadOrder locked_gamepad_order) {
			return HookMgr::Call<CInputActionMap*>(0x1409340B0, this, &id, size, locked_gamepad_order);
		}*/
	};

	class CInputDeviceManager : public IInputDeviceManager
	{
	public:
		//CInputDeviceManager();
		//~CInputDeviceManager();

		void SetInFocus(bool bInFocus) { m_IsInFocus = bInFocus; }

		uintptr_t* DirectInput8;
		uintptr_t* WindowHandle;
		bool		m_IsInFocus;
	};
}

class CDeviceManager_AVA // STEAM 0x160 - AVA 0x130
{
public:

	Input::CInputDeviceManager* GetInputManager() { return &m_InputManager; }

	char _unk000[0x70];
	Input::CInputDeviceManager m_InputManager;

};

class CDeviceManager_STEAM // STEAM 0x160 - AVA 0x130
{
public:

	Input::CInputDeviceManager* GetInputManager() { return &m_InputManager; }

	char _unk000[0xA0];
	Input::CInputDeviceManager m_InputManager;

};