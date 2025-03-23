#pragma once

#include <SDL3/SDL.h>
#include <memory>

class GameObjects;
class SDL_Renderer;
class GameState;

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

	int frameStep_{};
	Uint64 lastStep_ = 0;

	bool isPaused_{false};

	std::unique_ptr<GameObjects> gameObjects_;

	GameState* state_;
};