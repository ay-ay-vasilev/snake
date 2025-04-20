#include "Food.hpp"

#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <random>

void Food::init(std::pair<size_t, size_t> size, std::pair<int, int> offset)
{
	m_size = size;
	m_offset = offset;
}

void Food::update() {}

void Food::render(SDL_Renderer* renderer)
{
	for (const auto& food : m_foodPositions)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_FRect rect;

		rect.x = m_offset.first + food.first * m_size.first + 3;
		rect.y = m_offset.second + food.second * m_size.second + 3;
	
		rect.w = m_size.first - 6;
		rect.h = m_size.second - 6;

		SDL_RenderFillRect(renderer, &rect);
	}
}

bool Food::tryProcessFoodCollision(const std::pair<int, int>& position)
{
	if (std::find(m_foodPositions.begin(), m_foodPositions.end(), position) != m_foodPositions.end())
	{
		std::erase(m_foodPositions, position);
		return true;
	}

	return false;
}

void Food::spawnFood(const std::pair<size_t, size_t>& gridSize, const std::vector<std::deque<std::pair<int, int>>>& snakePositions)
{
	std::vector<std::pair<int, int>> emptyCells;
	for (size_t i = 0; i < gridSize.first; ++i)
	{
		for (size_t j = 0; j < gridSize.second; ++j)
			emptyCells.emplace_back(static_cast<int>(i), static_cast<int>(j));
	}

	for (const auto& snake : snakePositions)
	{
		for (const auto& element : snake)
		{
			if (std::find(emptyCells.begin(), emptyCells.end(), element) != emptyCells.end())
				std::erase(emptyCells, element);
		}
	}

	for (const auto& food : m_foodPositions)
	{
		if (std::find(emptyCells.begin(), emptyCells.end(), food) != emptyCells.end())
			std::erase(emptyCells, food);
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(0, emptyCells.size() - 1);

	auto randomIndex = dist(gen);
	m_foodPositions.emplace_back(emptyCells[randomIndex]);
}
