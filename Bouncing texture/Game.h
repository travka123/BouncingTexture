#pragma once

#include "Input.h"
#include "FlatObject.h"

static class Game {
public:
	static Input input;
	
	static void Think();
	static void Click(int x, int y);
	static void Relised();
	static void SetBoarders(RECT rect);
	static void SetHWND(HWND hWnd);
	static void Redraw(PAINTSTRUCT* ps);
	static void SetBitmap(HBITMAP bitmap);

private:
	static bool _isSelected;
};

