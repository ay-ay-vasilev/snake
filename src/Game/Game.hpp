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

	int m_frameStep{};
	Uint64 m_lastStep = 0;
	std::unique_ptr<GameObjects> m_gameObjects;
	GameState* m_state;
};