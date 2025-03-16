#pragma once

#include <SDL3/SDL.h>

#include "Grid.hpp"
#include "UI.hpp"

class SDL_Renderer;

class Game
{
public:
	void init();
	SDL_AppResult handleInput(void* appstate, SDL_Event* event);
	void update();
	void render(SDL_Renderer* renderer);

private:
	bool isRunning{true};

	Grid grid;
	UI ui;
};