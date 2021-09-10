#include "BouncingBehavior.h"

#include <cmath>
#include <stdlib.h>
#include <time.h>


#include "Defines.h"
#include "FlatObject.h"
#include "ControlingBehavior.h"

BouncingBehavior::BouncingBehavior() {
	srand(time(nullptr));
	int rint = rand();
	_speedX = (float)rint / RAND_MAX * BOUNCING_SPEED;
	_speedY = sqrt(BOUNCING_SPEED * BOUNCING_SPEED - _speedX * _speedX);
	switch (rint % 4) {
	case 1:
		_speedX = -_speedX;
		break;
	case 2:
		_speedY = -_speedY;
		break;
	case 3:
		_speedX = -_speedX;
		_speedY = -_speedY;
	}
}

void BouncingBehavior::Move(float x, float y)
{
	FlatObject::behavior = new ControlingBehavior();
	delete this;
}

void BouncingBehavior::Think() {
	BouncingMove(_speedX, _speedY);
}

void BouncingBehavior::BouncingMove(float shiftX, float shiftY) {
	bool verticalColision = false;
	bool horizontalColision = false;

	float beforVerticalColision = 0;
	float beforHorizontalColision = 0;

	do {

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

			float currentShiftY = shiftY > 0 ? (shiftY * (beforHorizontalColision / shiftX)) : 0;
			FlatObject::_posY += currentShiftY;

			_speedX = -_speedX;

			shiftX = -(shiftX - beforHorizontalColision);
			shiftY -= currentShiftY;

			horizontalColision = false;
		}
		else if (verticalColision) {
			FlatObject::_posY += beforVerticalColision;

			float currentShiftX = shiftX > 0 ? (shiftX * (beforVerticalColision / shiftX)) : 0;
			FlatObject::_posX += currentShiftX;

			_speedY = -_speedY;

			shiftX -= currentShiftX;
			shiftY = -(shiftY - beforVerticalColision);
			
			verticalColision = false;
		}
		else {
			FlatObject::_posX += shiftX;
			FlatObject::_posY += shiftY;
		}
	} while (horizontalColision || verticalColision);
}
