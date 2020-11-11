#include <string>

#include "Scene/SceneManager/SceneManager.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphic/GraphicManager.h"
#include "Engine/Input/InputManager.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE PrevInstance,
	LPSTR CmpLine,
	INT CmdShow)
{
	// ƒGƒ“ƒWƒ“•”‚Ì‰Šú‰»
	Window window;
	std::string title = "ClickGame";
	HWND handle;
	handle = window.MakeWindow(hInstance, 500, 500, title);
	if (THE_GRAPHIC.InitGraphics(handle) == false)
	{
		return -1;
	}
	if (THE_INPUT.Init(hInstance, handle) == false)
	{
		return -2;
	}

	SceneManager scene_manager;
	
	while (true)
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			scene_manager.Update();
			scene_manager.Draw();
		}
	}

	THE_INPUT.Release();
	THE_GRAPHIC.ReleaseGraphics();

	return 1;
}