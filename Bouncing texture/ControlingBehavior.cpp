#include "ControlingBehavior.h"

#include "FlatObject.h"
#include "BouncingBehavior.h"

int ControlingBehavior::_ticksBeforeBouncing = 180;

ControlingBehavior::ControlingBehavior()
{
	_ticksBeforeBouncingLeft = 180;
}

void ControlingBehavior::Move(float x, float y)
{
	if (x > 0) {
		if (FlatObject::_posX + FlatObject::_width + x < FlatObject::_boarders.right) {
			FlatObject::_posX += x;
		}
		else {
			FlatObject::_posX = FlatObject::_boarders.right - FlatObject::_width;
		}
	}
	else if (x < 0){
		if (FlatObject::_posX + x > 0) {
			FlatObject::_posX += x;
		}
		else {
			FlatObject::_posX = 0;
		}
	}

	if (y > 0) {
		if (FlatObject::_posY + FlatObject::_width + y < FlatObject::_boarders.bottom) {
			FlatObject::_posY += y;
		}
		else {
			FlatObject::_posY = FlatObject::_boarders.bottom - FlatObject::_height;
		}
	}
	else if (y < 0){
		if (FlatObject::_posY + y > 0) {
			FlatObject::_posY += y;
		}
		else {
			FlatObject::_posY = 0;
		}
	}
	_ticksBeforeBouncingLeft = _ticksBeforeBouncing;
}

void ControlingBehavior::Think()
{
	_ticksBeforeBouncingLeft--;
	if (_ticksBeforeBouncingLeft <= 0) {
		FlatObject::behavior = new BouncingBehavior();
		delete this;
	}
}
