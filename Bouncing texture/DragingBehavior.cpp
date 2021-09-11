#include "DragingBehavior.h"

#include "FlatObject.h"
#include "ControlingBehavior.h"

void DragingBehavior::Released()
{
	FlatObject::behavior = new ControlingBehavior();
	delete this;
}

void DragingBehavior::MouseMove(int x, int y)
{
	if (x < 0) {
		FlatObject::_posX = 0;
	}
	else if (x + FlatObject::_width < FlatObject::_boarders.right){
		FlatObject::_posX = x;
	}
	else {
		FlatObject::_posX = FlatObject::_boarders.right - FlatObject::_width;
	}

	if (y < 0) {
		FlatObject::_posY = 0;
	} 
	else if (y + FlatObject::_height < FlatObject::_boarders.bottom) {
		FlatObject::_posY = y;
	}
	else {
		FlatObject::_posY = FlatObject::_boarders.bottom - FlatObject::_height;
	}
}
