#pragma once

#include <SDL3_image/SDL_image.h>
#include <utility>

class Grid
{
public:
	Grid() : m_gridSize(), m_cellSize(), m_offset() {}

	void init(
		std::pair<size_t, size_t> gridSize = {0, 0},
		std::pair<size_t, size_t> cellSize = {0, 0},
		std::pair<int, int> offset = {0, 0});
	void update();
	void render(SDL_Renderer* renderer);

	bool isCollision(const std::pair<int, int>& position) const;

private:
	std::pair<size_t, size_t> m_gridSize{0,0};
	std::pair<size_t, size_t> m_cellSize{0,0};
	std::pair<int, int> m_offset{0,0};
};