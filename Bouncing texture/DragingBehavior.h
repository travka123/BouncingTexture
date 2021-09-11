#pragma once

#include "FlatObjectBehavior.h"

class DragingBehavior : public FlatObjectBehavior {
public:
	void Released();
	void MouseMove(int x, int y);
};