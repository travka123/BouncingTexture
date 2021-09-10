#include "BouncingBehavior.h"

#include <cmath>

#include "Defines.h"
#include "FlatObject.h"

BouncingBehavior::BouncingBehavior() {
	_speedX = rand() % (2 * (OBJECT_SPEED)+1) - OBJECT_SPEED;
	_speedY = (int)sqrt(OBJECT_SPEED * OBJECT_SPEED - _speedX * _speedX);
	_speedY = (rand() % 2) ? _speedY : -_speedY;
}

void BouncingBehavior::Think() {
	Move(_speedX, _speedY);
}

void BouncingBehavior::Move(float shiftX, float shiftY) {
	bool verticalColision = false;
	bool horizontalColision = false;

	float beforVerticalColision = 0;
	float beforHorizontalColision = 0;

	if ((FlatObject::_width < FlatObject::_boarders.right) && (shiftX != 0)) {
		if (shiftX + FlatObject::_posX < 0) {
			horizontalColision = true;
			beforHorizontalColision = -FlatObject::_posX;
		}
		else if (shiftX + FlatObject::_posX + FlatObject::_width > FlatObject::_boarders.right) {
			horizontalColision = true;
			beforHorizontalColision = FlatObject::_boarders.right - FlatObject::_posX - FlatObject::_width;
		}
	}
	else {
		shiftX = 0;
	}

	if ((FlatObject::_height < FlatObject::_boarders.bottom) && (shiftY != 0)) {
		if (shiftY + FlatObject::_posY < 0) {
			verticalColision = true;
			beforVerticalColision = -FlatObject::_posY;
		}
		else if (shiftY + FlatObject::_posY + FlatObject::_height > FlatObject::_boarders.bottom) {
			verticalColision = true;
			beforVerticalColision = FlatObject::_boarders.bottom - FlatObject::_posY - FlatObject::_height;
		}
	}
	else {
		shiftY = 0;
	}

	if (horizontalColision && verticalColision) {
		horizontalColision = beforHorizontalColision / _speedX < beforVerticalColision / _speedY;
		verticalColision = !horizontalColision;
	}

	if (horizontalColision) {
		FlatObject::_posX += beforHorizontalColision;

		float currentShiftY = (shiftY * (beforHorizontalColision / shiftX));
		FlatObject::_posY += currentShiftY;

		_speedX = -_speedX;

		Move(-(shiftX - beforHorizontalColision), shiftY - currentShiftY);
	}
	else if (verticalColision) {
		FlatObject::_posY += beforVerticalColision;

		float currentShiftX = (shiftX * (beforVerticalColision / shiftX));
		FlatObject::_posX += currentShiftX;

		_speedY = -_speedY;

		Move(shiftX - currentShiftX, -(shiftY - beforVerticalColision));
	}
	else {
		FlatObject::_posX += shiftX;
		FlatObject::_posY += shiftY;
	}
}
