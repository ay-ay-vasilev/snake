#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "Constants.hpp"

void Game::init()
{
	grid = Grid({GRID_SIZE, GRID_SIZE}, {CELL_SIZE, CELL_SIZE});
	grid.init();
	ui.init();
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT || (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE))
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_W)
	{
		ui.addScore(10);
		return SDL_APP_CONTINUE;
	}

	return SDL_APP_CONTINUE;
}

void Game::update()
{
	grid.update();
	ui.update();
}

void Game::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	grid.render(renderer);
	ui.render(renderer);

	SDL_RenderPresent(renderer);
}
