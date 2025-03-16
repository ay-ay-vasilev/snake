#pragma once

#include <vector>

class SDL_Renderer;

class Grid
{
public:
	Grid() : gridSize(), cellSize() {}
	Grid(std::pair<int, int> gridSize, std::pair<int, int> cellSize) : gridSize(gridSize), cellSize(cellSize) {}

	void init();
	void update();
	void render(SDL_Renderer* renderer);

private:
	std::pair<int, int> gridSize;
	std::pair<int, int> cellSize;
	std::vector<std::vector<int>> grid;
};