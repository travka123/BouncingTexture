#pragma once

#include "FlatObjectBehavior.h"

class BouncingBehavior : public FlatObjectBehavior {
public:
	BouncingBehavior();

	void Move(float x, float y);
	void Think();
private:
	float _speedX;
	float _speedY;

	void BouncingMove(float shiftX, float shiftY);
};

