#pragma once

#include "Input.h"

class Game {
public:
	Game();

	Input input;

	static Game* Instance();

private:
	static Game* _instance;
};

