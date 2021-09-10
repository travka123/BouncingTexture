#include "Game.h"
#include "Defines.h"
#include "Render.h"

Input Game::input;
bool Game::_isSelected;

void Game::Think() {
	float horizontalMove = (input.moveRight - input.moveLeft + input.horizontalScroll) * MOVE_SPEED / TARGET_FPS;
	float verticalMove = (input.moveDown - input.moveUp + input.verticalScroll) * MOVE_SPEED / TARGET_FPS;

	RECT oldRect, newRect, invalideRect;
	FlatObject::GetRect(&oldRect);

	if (horizontalMove || verticalMove) {
		FlatObject::Move(horizontalMove, verticalMove);
	}
	FlatObject::Think();

	FlatObject::GetRect(&newRect);

	invalideRect.left = oldRect.left < newRect.left ? oldRect.left : newRect.left;
	invalideRect.right = oldRect.right > newRect.right ? oldRect.right : newRect.right;
	invalideRect.top = oldRect.top < newRect.top ? oldRect.top : newRect.top;
	invalideRect.bottom = oldRect.bottom > newRect.bottom ? oldRect.bottom : newRect.bottom;

	Render::Invalidate(&invalideRect);
}

void Game::Click(int x, int y) {
	if (FlatObject::IsTouching(x, y)) {
		_isSelected = true;
		FlatObject::Clicked();
	}
}

void Game::Relised() {
	if (_isSelected) {
		FlatObject::Released();
		_isSelected = false;
	}
}

void Game::SetBoarders(RECT rect) {
	FlatObject::SetBoarders(rect);
}

void Game::SetHWND(HWND hWnd) {
	Render::SetHWND(hWnd);
}

void Game::Redraw(PAINTSTRUCT* pps) {
	Render::Redraw(pps);
}

void Game::SetBitmap(HBITMAP bitmap) {
	Render::SetBitmap(bitmap);
}


