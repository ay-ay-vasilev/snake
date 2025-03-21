#include "Grid.hpp"

void Grid::init(std::pair<size_t, size_t> gridSize, std::pair<size_t, size_t> cellSize, std::pair<int, int> offset)
{
	gridSize_ = gridSize;
	cellSize_ = cellSize;
	offset_ = offset;
}

void Grid::update() {}

void Grid::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

	for (size_t i = 0; i < gridSize_.first; ++i)
	{
		for (size_t j = 0; j < gridSize_.second; ++j)
		{
			SDL_FRect rect;

			rect.x = offset_.first + i * cellSize_.first;
			rect.y = offset_.second + j * cellSize_.second;

			rect.w = cellSize_.first;
			rect.h = cellSize_.second;
			SDL_RenderRect(renderer, &rect);
		}
	}
}

bool Grid::isCollision(const std::pair<int, int>& position) const
{
	const auto& x = std::get<0>(position);
	const auto& y = std::get<1>(position);

	return (x < 0 || x >= gridSize_.first || y < 0 || y >= gridSize_.second);
}