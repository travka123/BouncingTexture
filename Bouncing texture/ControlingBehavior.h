#pragma once

#include "FlatObjectBehavior.h"

class ControlingBehavior : public FlatObjectBehavior
{
public:
	ControlingBehavior();

	void Move(float x, float y);
	void Think();

private:
	static int _ticksBeforeBouncing;

	int _ticksBeforeBouncingLeft;
};

