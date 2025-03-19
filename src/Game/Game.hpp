#pragma once

#include <SDL3/SDL.h>

#include <memory>

class Grid;
class Snake;
class UI;
class SDL_Renderer;

class Game
{
public:
	Game();
	~Game();

	void init();
	SDL_AppResult handleInput(void* appstate, SDL_Event* event);
	SDL_AppResult gameLoop(void* appstate, SDL_Renderer* renderer);

private:
	void update();
	void render(SDL_Renderer* renderer);

	int frameStep{};
	Uint64 lastStep = 0;

	std::unique_ptr<Grid> grid;
	std::unique_ptr<Snake> snake;
	std::unique_ptr<UI> ui;

};