#pragma once

#include <SDL3_image/SDL_image.h>
#include <utility>

class Grid
{
public:
	Grid() : gridSize(), cellSize(), offset() {}
	Grid(std::pair<size_t, size_t> gridSize, std::pair<size_t, size_t> cellSize, std::pair<int, int> offset) : gridSize(gridSize), cellSize(cellSize), offset(offset) {}

	void init();
	void update();
	void render(SDL_Renderer* renderer);

private:
	std::pair<size_t, size_t> gridSize;
	std::pair<size_t, size_t> cellSize;
	std::pair<int, int> offset;
};