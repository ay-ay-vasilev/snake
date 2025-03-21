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
	void reset();

	bool checkCollision(const std::pair<int, int>& position) const;

	int frameStep_{};
	Uint64 lastStep_ = 0;
	bool isPaused_{false};

	std::unique_ptr<Grid> grid_;
	std::unique_ptr<Snake> snake_;
	std::unique_ptr<UI> ui_;

};