#pragma once

#include <vector>
#include <deque>

struct SDL_Renderer;

class Food
{
public:
	void init(
		std::pair<size_t, size_t> size = {0,0},
		std::pair<int, int> offset = {0,0}
	);
	void update();
	void render(SDL_Renderer* renderer);

	bool isFoodAbsent() const { return m_foodPositions.empty(); }
	int getFoodCount() const { return m_foodPositions.size(); }
	bool tryProcessFoodCollision(const std::pair<int, int>& position);
	void spawnFood(const std::pair<size_t, size_t>& gridSize, const std::vector<std::deque<std::pair<int, int>>>& snakePositions);

private:
	bool isFoodCollision(const std::pair<int, int>& position) const;

	std::vector<std::pair<int, int>> m_foodPositions;
	std::pair<size_t, size_t> m_size{0, 0};
	std::pair<int, int> m_offset{0, 0};
};
