#include "Grid.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Constants.hpp"

void Grid::init()
{
	for (auto i = 0; i < gridSize.first; ++i)
	{
		std::vector<int> gridLine;
		for (auto j = 0; j < gridSize.second; ++j)
			gridLine.emplace_back(0);
		grid.emplace_back(gridLine);
	}
}

void Grid::update() {}

void Grid::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

	const auto gridWidth = gridSize.first * cellSize.first;
	const auto gridHeight = gridSize.second * cellSize.second;
	const std::pair<int, int> offset
	{
		(WINDOW_WIDTH - gridWidth) / 2,
		(WINDOW_HEIGHT - gridHeight) / 2
	};

	int row{0}, col{0};
	for (const auto& gridLine : grid)
	{
		for (const auto& cell : gridLine)
		{
			SDL_FRect rect;

			rect.x = offset.first + row * cellSize.first;
			rect.y = offset.second + col * cellSize.second;

			rect.w = cellSize.first;
			rect.h = cellSize.second;
			SDL_RenderRect(renderer, &rect);
			++col;
		}
		col = 0;
		++row;
	}
}