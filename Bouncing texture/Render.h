#pragma once

#include <Windows.h>

static class Render {
public:
	static void Invalidate(RECT* rect);
	static void Redraw(PAINTSTRUCT* pps);
	static void SetHWND(HWND _hWnd);
	static void SetBitmap(HBITMAP bitmap);

private:
	static HWND _hWnd;
	static HBITMAP _bitmap;
	static int _width;
	static int _height;
};

