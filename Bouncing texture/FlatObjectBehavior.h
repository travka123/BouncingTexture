#pragma once

class FlatObjectBehavior {
public:
	virtual void Clicked() { }
	virtual void Released() { }
	virtual void Move(float x, float y) { }
	virtual void Think() { }
	virtual void MouseMove(int x, int y) { }
};