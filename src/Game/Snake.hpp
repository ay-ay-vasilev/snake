#pragma once

#include <SDL3_image/SDL_image.h>
#include <deque>
#include <queue>
#include <optional>

class Snake
{
public:
	Snake(
		std::deque<std::pair<int, int>> initPos,
		std::pair<size_t, size_t> size,
		std::pair<int, int> offset
	);

	enum class eDirection
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	void init();
	void update();
	void render(SDL_Renderer* renderer);

	inline const int getDirection() const { return static_cast<int>(direction); };
	void setDirection(eDirection newDirection);

private:
	void move();
	std::optional<eDirection> getDirectionFromQueue();
	std::optional<eDirection> getInitialDirection();

	std::deque<std::pair<int, int>> partPositions;
	std::pair<size_t, size_t> size{0, 0};
	std::pair<int, int> offset{0, 0};

	bool isMoving{false};
	bool isChangingDirection{false};

	eDirection direction{eDirection::RIGHT};
	std::queue<eDirection> directionQueue;
};