#include "Grid.hpp"

void Grid::init(std::pair<size_t, size_t> gridSize, std::pair<size_t, size_t> cellSize, std::pair<int, int> offset)
{
	m_gridSize = gridSize;
	m_cellSize = cellSize;
	m_offset = offset;
}

void Grid::update() {}

void Grid::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

	for (size_t i = 0; i < m_gridSize.first; ++i)
	{
		for (size_t j = 0; j < m_gridSize.second; ++j)
		{
			SDL_FRect rect;

			rect.x = m_offset.first + i * m_cellSize.first;
			rect.y = m_offset.second + j * m_cellSize.second;

			rect.w = m_cellSize.first;
			rect.h = m_cellSize.second;
			SDL_RenderRect(renderer, &rect);
		}
	}
}

bool Grid::isCollision(const std::pair<int, int>& position) const
{
	const auto& x = std::get<0>(position);
	const auto& y = std::get<1>(position);

	return (x < 0 || x >= m_gridSize.first || y < 0 || y >= m_gridSize.second);
}