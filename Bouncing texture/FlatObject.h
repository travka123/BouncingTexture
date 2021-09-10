#pragma once

#include <Windows.h>

#include "FlatObjectBehavior.h"
#include "BouncingBehavior.h"
#include "ControlingBehavior.h"

static class FlatObject {
public:
	static void Move(float x, float y);
	static bool IsTouching(int x, int y);
	static void SetBoarders(RECT boarders);
	static void Clicked();
	static void Released();
	static void GetRect(RECT *rect);
	static void Think();

private:
	friend class FlatObjectBehavior;
	friend class BouncingBehavior;
	friend class ControlingBehavior;

	static FlatObjectBehavior* behavior;
	static float _posX;
	static float _posY;
	static int _width;
	static int _height;
	static RECT _boarders;
};

