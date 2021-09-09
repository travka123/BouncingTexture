#include <Windows.h>
#include <windowsx.h>

#include "Defines.h"
#include "Game.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow) {

	const wchar_t className[] = L"MyWindowClass";

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = wcex.hIcon;

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(className, L"Bouncing texture",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

void MouseMove(short x, short y) {
	Game* game = Game::Instance();
	game->input.mouseX = x;
	game->input.mouseY = y;
}

void KeyStateChange(WPARAM keyCode, bool pressed) {
	Game* game = Game::Instance();
	switch (keyCode) {
	case VK_UP:
	case 0x57:
		game->input.moveUp = pressed;
		break;

	case VK_DOWN:
	case 0x53:
		game->input.moveDown = pressed;
		break;

	case VK_LEFT:
	case 0x41:
		game->input.moveLeft = pressed;
		break;

	case VK_RIGHT:
	case 0x44:
		game->input.moveRight = pressed;
		break;
	}
}

void MouseWheel(short rotation, short flags) {
	Game* game = Game::Instance();
	if (flags && MK_SHIFT) {
		game->input.horizontalScroll -= rotation / WHEEL_DELTA * WHELL_FORCE;
	}
	else {
		game->input.verticalScroll -= rotation / WHEEL_DELTA * WHELL_FORCE;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_MOUSEMOVE:
		MouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_KEYDOWN:
		KeyStateChange(wParam, true);
		break;

	case WM_KEYUP:
		KeyStateChange(wParam, false);

	case WM_MOUSEWHEEL:
		MouseWheel(GET_WHEEL_DELTA_WPARAM(wParam), wParam & 0xFFFF);
		break;
  
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

