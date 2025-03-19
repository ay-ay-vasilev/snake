#include "Grid.hpp"

void Grid::init() {}

void Grid::update() {}

void Grid::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

	for (size_t i = 0; i < gridSize.first; ++i)
	{
		for (size_t j = 0; j < gridSize.second; ++j)
		{
			SDL_FRect rect;

			rect.x = offset.first + i * cellSize.first;
			rect.y = offset.second + j * cellSize.second;

			rect.w = cellSize.first;
			rect.h = cellSize.second;
			SDL_RenderRect(renderer, &rect);
		}
	}
}