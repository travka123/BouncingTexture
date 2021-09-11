#pragma once

#include <Windows.h>

#include "FlatObjectBehavior.h"
#include "BouncingBehavior.h"
#include "ControlingBehavior.h"
#include "DragingBehavior.h"

static class FlatObject {
public:
	static void Move(float x, float y);
	static void SetBoarders(RECT boarders);
	static void Clicked();
	static void Released();
	static void GetRect(RECT *rect);
	static void Think();
	static void MouseMove(int x, int y);

private:
	friend class FlatObjectBehavior;
	friend class BouncingBehavior;
	friend class ControlingBehavior;
	friend class DragingBehavior;

	static FlatObjectBehavior* behavior;
	static float _posX;
	static float _posY;
	static int _width;
	static int _height;
	static RECT _boarders;
};

