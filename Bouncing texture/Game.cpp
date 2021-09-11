#include "Game.h"
#include "Defines.h"
#include "Render.h"

Input Game::input;
bool Game::_isSelected;

short Game::_lastMouseX = 0;
short Game::_lastMouseY = 0;

int Game::_normMouseX = 0;
int Game::_normMouseY = 0;

void Game::Think() {
	float horizontalMove = (input.moveRight - input.moveLeft + input.horizontalScroll) * CONTROL_SPEED / TARGET_FPS;
	float verticalMove = (input.moveDown - input.moveUp + input.verticalScroll) * CONTROL_SPEED / TARGET_FPS;

	input.horizontalScroll = 0;
	input.verticalScroll = 0;

	RECT oldRect, newRect, invalideRect;
	FlatObject::GetRect(&oldRect);

	if (horizontalMove || verticalMove) {
		FlatObject::Move(horizontalMove, verticalMove);
	}

	if (_isSelected && ((_lastMouseX != input.mouseX) || (_lastMouseY != input.mouseY))) {
		FlatObject::MouseMove(input.mouseX - _normMouseX, input.mouseY - _normMouseY);
	}

	_lastMouseX = input.mouseX;
	_lastMouseY = input.mouseY;

	if (input.resized) {
		RECT clientRect;
		Render::ClientRect(&clientRect);
		FlatObject::SetBoarders(clientRect);
	}
	input.resized = false;
	
	FlatObject::Think();

	FlatObject::GetRect(&newRect);

	invalideRect.left = oldRect.left < newRect.left ? oldRect.left : newRect.left;
	invalideRect.right = oldRect.right > newRect.right ? oldRect.right : newRect.right;
	invalideRect.top = oldRect.top < newRect.top ? oldRect.top : newRect.top;
	invalideRect.bottom = oldRect.bottom > newRect.bottom ? oldRect.bottom : newRect.bottom;

	

	

	Render::Invalidate(&invalideRect);
}

void Game::Click(int x, int y) {
	if (Render::IsTouching(x, y)) {
		_isSelected = true;
		FlatObject::Clicked();

		RECT rect;
		FlatObject::GetRect(&rect);
		_normMouseX = x - rect.left;
		_normMouseY = y - rect.top;
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


