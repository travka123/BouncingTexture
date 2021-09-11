#include <Windows.h>
#include <windowsx.h>

#include "Defines.h"
#include "Game.h"

#define IDT_TIMER1 1

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

	SetTimer(hWnd, IDT_TIMER1, 1000 / TARGET_FPS, nullptr);

	Game::SetHWND(hWnd);

	RECT rect;
	GetClientRect(hWnd, &rect);
	Game::SetBoarders(rect);

	Game::SetBitmap((HBITMAP)LoadImage(hInstance, L"Media\\bitmap.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		//TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

void MouseMove(short x, short y) {
		Game::input.mouseX = x;
		Game::input.mouseY = y;
}

void KeyStateChange(WPARAM keyCode, bool pressed) {
	switch (keyCode) {
	case VK_UP:
	case 0x57:
		Game::input.moveUp = pressed;
		break;

	case VK_DOWN:
	case 0x53:
		Game::input.moveDown = pressed;
		break;

	case VK_LEFT:
	case 0x41:
		Game::input.moveLeft = pressed;
		break;

	case VK_RIGHT:
	case 0x44:
		Game::input.moveRight = pressed;
		break;
	}
}

void MouseWheel(short rotation, short flags) {
	if (flags && MK_SHIFT) {
		Game::input.horizontalScroll -= rotation / WHEEL_DELTA * WHELL_FORCE;
	}
	else {
		Game::input.verticalScroll -= rotation / WHEEL_DELTA * WHELL_FORCE;
	}
}

void MouseLBDown(short x, short y) {
	Game::Click(x, y);
}

void MouseLBUp() {
	Game::Relised();
}

void OnTick() {
	Game::Think();
}

void Paint(HWND hWnd) {
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);
	Game::Redraw(&ps);
	EndPaint(hWnd, &ps);
}

void Resized() {
	Game::input.resized = true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	
	case WM_TIMER:
		OnTick();
		break;

	case WM_PAINT:
		Paint(hWnd);
		break;

	case WM_MOUSEMOVE:
		MouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_KEYDOWN:
		KeyStateChange(wParam, true);
		break;

	case WM_KEYUP:
		KeyStateChange(wParam, false);
		break;

	case WM_MOUSEWHEEL:
		MouseWheel(GET_WHEEL_DELTA_WPARAM(wParam), wParam & 0xFFFF);
		break;

	case WM_LBUTTONDOWN:
		MouseLBDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_LBUTTONUP:
		MouseLBUp();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		Resized();
		break;
  
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

