#pragma once

#include <SDL3_image/SDL_image.h>
#include <deque>
#include <queue>
#include <optional>

class Snake
{
public:
	Snake();

	enum class eDirection
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	void init(
		std::deque<std::pair<int, int>> initPartPositions = {{0,0}},
		std::pair<size_t, size_t> size = {0,0},
		std::pair<int, int> offset = {0,0}
	);
	void update();
	void render(SDL_Renderer* renderer);

	void setDirection(eDirection newDirection);
	void undoMove();
	void grow();
	const bool isSnakeCollision(const std::pair<int, int>& position) const;
	inline const std::pair<int, int>& getHeadPosition() const { return m_partPositions.front(); }
	inline const std::deque<std::pair<int, int>>& getPartPositions() const { return m_partPositions; }

private:
	void move();
	std::optional<eDirection> getDirectionFromQueue();
	std::optional<eDirection> getInitialDirection() const;
	std::pair<int, int> getNextPosition() const;

	std::deque<std::pair<int, int>> m_partPositions;
	std::pair<size_t, size_t> m_size{0, 0};
	std::pair<int, int> m_offset{0, 0};
	std::optional<std::pair<int, int>> m_prevTail;
	eDirection m_direction{eDirection::RIGHT};
	std::queue<eDirection> m_directionQueue;
};