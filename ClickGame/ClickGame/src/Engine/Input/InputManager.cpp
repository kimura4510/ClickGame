#include "InputManager.h"
#include "..//Window/Window.h"
#include <d3dx9math.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

InputManager::InputManager() : MouseDevice(nullptr)
{
	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		MouseState[i] = InputState::Not_Push;
	}
}

bool InputManager::Init(HINSTANCE instance, HWND window_handle)
{
	// Interface‚Ì¶¬
	if (FAILED(DirectInput8Create(instance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&Interface,
		nullptr)))
	{
		return false;
	}

	if (CreateMouseDevice(window_handle) == false)
	{
		return false;
	}

	return true;
}

bool InputManager::CreateMouseDevice(HWND window_handle)
{
	if (FAILED(Interface->CreateDevice(GUID_SysMouse, &MouseDevice, nullptr)))
	{
		return false;
	}

	if (FAILED(MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		MouseDevice->Release();
		MouseDevice = nullptr;
		return false;
	}

	if (FAILED(MouseDevice->SetCooperativeLevel(window_handle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		MouseDevice->Release();
		MouseDevice = nullptr;
		return false;
	}

	if (FAILED(MouseDevice->Acquire()))
	{
		MouseDevice->Release();
		MouseDevice = nullptr;
		return false;
	}

	MouseDevice->Poll();

	return true;
}

void InputManager::Release()
{
	if (MouseDevice != nullptr)
	{
		MouseDevice->Unacquire();
		MouseDevice->Release();
		MouseDevice = nullptr;
	}

	Interface->Release();
}

void InputManager::Update()
{
	UpdateMouseState();
}

void InputManager::UpdateMouseState()
{
	DIMOUSESTATE mouse_state;

	if (FAILED(MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state)))
	{
		MouseDevice->Acquire();
		MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state);
	}

	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		if (mouse_state.rgbButtons[i] & 0x80)
		{
			if (MouseState[i] == InputState::Not_Push || MouseState[i] == InputState::Release)
			{
				MouseState[i] = InputState::Push_Down;
			}
			else
			{
				MouseState[i] = InputState::Push;
			}
		}
		else
		{
			if (MouseState[i] == InputState::Push || MouseState[i] == InputState::Push_Down)
			{
				MouseState[i] = InputState::Release;
			}
			else
			{
				MouseState[i] = InputState::Not_Push;
			}
		}
	}
}

bool InputManager::GetMouse(MouseButton button) const
{
	if (MouseState[static_cast<int>(button)] == InputState::Push)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseDown(MouseButton button) const
{
	if (MouseState[static_cast<int>(button)] == InputState::Push_Down)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseUp(MouseButton button) const
{
	if (MouseState[static_cast<int>(button)] == InputState::Release)
	{
		return true;
	}
	return false;
}

POINT InputManager::GetMousePos() const
{
	POINT position;
	GetCursorPos(&position);

	float horizon_magnification = (float)GetSystemMetrics(SM_CXSCREEN) / 1920.0f;
	float vertical_magnification = (float)GetSystemMetrics(SM_CYSCREEN) / 1080.0f;
	position.x /= horizon_magnification;
	position.y /= vertical_magnification;

	return position;
}