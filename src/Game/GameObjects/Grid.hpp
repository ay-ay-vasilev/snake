#pragma once

#include <utility>

struct SDL_Renderer;

class Grid
{
public:
	Grid() : m_gridSize(), m_cellSize(), m_offset() {}

	void init(
		std::pair<std::size_t, std::size_t> gridSize = {0, 0},
		std::pair<std::size_t, std::size_t> cellSize = {0, 0},
		std::pair<int, int> offset = {0, 0});
	void update();
	void render(SDL_Renderer* renderer);

	bool isWallCollision(const std::pair<int, int>& position) const;
	const std::pair<std::size_t, std::size_t>& getGridSize() const { return m_gridSize; }

private:
	std::pair<std::size_t, std::size_t> m_gridSize{0,0};
	std::pair<std::size_t, std::size_t> m_cellSize{0,0};
	std::pair<int, int> m_offset{0,0};
};
