#include "FlatObject.h"

#include "Defines.h"
#include "BouncingBehavior.h"

float FlatObject::_posX;
float FlatObject::_posY;

int FlatObject::_width = OBJECT_WIDTH;
int FlatObject::_height = OBJECT_HEIGHT;

RECT FlatObject::_boarders;

FlatObjectBehavior* FlatObject::behavior = new BouncingBehavior();

void FlatObject::Move(float x, float y) {}

bool FlatObject::IsTouching(int x, int y) {
	return false;
}

void FlatObject::SetBoarders(RECT boarders) {
	_boarders = boarders;
}

void FlatObject::Clicked() {}

void FlatObject::Released() {}

void FlatObject::GetRect(RECT* rect) {
	rect->left = _posX;
	rect->top = _posY;
	rect->right = _posX + _width;
	rect->bottom = _posY + _height;
}

void FlatObject::Think() {
	behavior->Think();
}
