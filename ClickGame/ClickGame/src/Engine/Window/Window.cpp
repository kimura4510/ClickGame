#include "Window.h"

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}
	return 0;
}

HWND Window::MakeWindow(HINSTANCE instance, int width, int height, std::string title)
{
	HWND hwnd;
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WindowProc,
		0,
		0,
		instance,
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),
		LoadCursor(NULL, IDC_ARROW),
		nullptr,
		nullptr,
		WINDOW_CLASS_NAME,
		nullptr
	};

	//構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return 0;
	}

	//ウィンドウの作成
	hwnd = CreateWindow(
		WINDOW_CLASS_NAME,
		title.c_str(),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		CW_USEDEFAULT,
		0,
		width,
		height,
		nullptr,
		nullptr,
		instance,
		nullptr);

	if (hwnd == nullptr)
	{
		return 0;
	}

	RECT window_rect;
	RECT client_rect;

	if (GetWindowRect(hwnd, &window_rect) == false || 
		GetClientRect(hwnd, &client_rect) == false)
	{
		return 0;
	}

	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);
	int width_size = frame_size_x + width;
	int height_size = frame_size_y + height;

	SetWindowPos(hwnd, nullptr, CW_USEDEFAULT, CW_USEDEFAULT, width_size, height_size, SWP_NOMOVE);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return hwnd;
}