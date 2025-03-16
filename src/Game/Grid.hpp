#pragma once

#include <SDL3_image/SDL_image.h>
#include <vector>

class Grid
{
public:
	Grid() : gridSize(), cellSize(), offset() {}
	Grid(std::pair<int, int> gridSize, std::pair<int, int> cellSize, std::pair<int, int> offset) : gridSize(gridSize), cellSize(cellSize), offset(offset) {}

	void init();
	void update();
	void render(SDL_Renderer* renderer);

private:
	std::pair<int, int> gridSize;
	std::pair<int, int> cellSize;
	std::pair<int, int> offset;
	std::vector<std::vector<int>> grid;
};