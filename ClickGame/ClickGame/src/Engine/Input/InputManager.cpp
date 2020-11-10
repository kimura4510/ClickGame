#include "InputManager.h"
#include "..//Window/Window.h"
#include <d3dx9math.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")

struct GamePadEnumParam
{
	LPDIRECTINPUTDEVICE8* GamePadDevList;
	int FindCount;
	HWND windowhandle;
};

InputManager::InputManager() : MouseDevice(nullptr)
{
	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		MouseState[i] = InputState::Not_Push;
	}
}

bool InputManager::Init(HINSTANCE hInstance_, HWND hWindow_)
{
	// Interface‚Ì¶¬
	if (FAILED(DirectInput8Create(hInstance_,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&Interface,
		NULL)))
	{
		return false;
	}

	if (CreateMouseDevice(hWindow_) == false)
	{
		return false;
	}

	return true;
}

bool InputManager::CreateMouseDevice(HWND hWindow_)
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

	if (FAILED(MouseDevice->SetCooperativeLevel(hWindow_, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
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
	DIMOUSESTATE mouse;

	if (FAILED(MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse)))
	{
		MouseDevice->Acquire();
		MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse);
	}

	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		if (mouse.rgbButtons[i] & 0x80)
		{
			if (MouseState[i] == InputState::Not_Push || MouseState[i] == InputState::Release)
			{
				MouseState[i] = InputState::PushDown;
			}
			else
			{
				MouseState[i] = InputState::Push;
			}
		}
		else
		{
			if (MouseState[i] == InputState::Push || MouseState[i] == InputState::PushDown)
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

bool InputManager::GetMouse(MouseButton btn_) const
{
	if (MouseState[static_cast<int>(btn_)] == InputState::Push)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseDown(MouseButton btn_) const
{
	if (MouseState[static_cast<int>(btn_)] == InputState::PushDown)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseUp(MouseButton btn_) const
{
	if (MouseState[static_cast<int>(btn_)] == InputState::Release)
	{
		return true;
	}
	return false;
}

POINT InputManager::GetMousePos() const
{
	POINT pos;
	GetCursorPos(&pos);


	//ScreenToClient(THE_WINDOW->GetWindowHandle(), &pos);


	float horizon_magnification = (float)GetSystemMetrics(SM_CXSCREEN) / 1920.0f;
	float vertical_magnification = (float)GetSystemMetrics(SM_CYSCREEN) / 1080.0f;
	pos.x /= horizon_magnification;
	pos.y /= vertical_magnification;


	return pos;
}