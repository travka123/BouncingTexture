#include "FlatObject.h"

#include "Defines.h"
#include "BouncingBehavior.h"

float FlatObject::_posX;
float FlatObject::_posY;

int FlatObject::_width = OBJECT_WIDTH;
int FlatObject::_height = OBJECT_HEIGHT;

RECT FlatObject::_boarders;

FlatObjectBehavior* FlatObject::behavior = new BouncingBehavior();

void FlatObject::Move(float x, float y) {
	behavior->Move(x, y);
}

void FlatObject::SetBoarders(RECT boarders) {
	if (_posX + _width > boarders.right) {
		_posX = boarders.right - _width;
		_posX = (_posX < 0) ? 0 : _posX;
	}

	if (_posY + _height > boarders.bottom) {
		_posY = boarders.bottom - _height;
		_posY = (_posY < 0) ? 0 : _posY;
	}

	_boarders = boarders;
}

void FlatObject::Clicked() {
	behavior->Clicked();
}

void FlatObject::Released() {
	behavior->Released();
}

void FlatObject::GetRect(RECT* rect) {
	rect->left = _posX;
	rect->top = _posY;
	rect->right = _posX + _width;
	rect->bottom = _posY + _height;
}

void FlatObject::Think() {
	behavior->Think();
}

void FlatObject::MouseMove(int x, int y)
{
	behavior->MouseMove(x, y);
}
