#include "Game.h"

Game* Game::_instance = nullptr;

Game::Game() {
	input = { };
}

Game* Game::Instance() {
	if (_instance == nullptr) {
		_instance = new Game();
	}
	return _instance;
}
