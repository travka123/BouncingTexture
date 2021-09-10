#pragma once

class FlatObjectBehavior {
public:
	virtual void Clicked() { }
	virtual void Released() { }
	virtual void Move() { }
	virtual void Think() { }
};