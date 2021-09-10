#pragma once

#include "FlatObjectBehavior.h"

class BouncingBehavior : public FlatObjectBehavior {
public:
	BouncingBehavior();

	void Think();
private:
	int _speedX;
	int _speedY;

	void Move(float shiftX, float shiftY);
};

