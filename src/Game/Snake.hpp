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

	inline const int getDirection() const { return static_cast<int>(direction_); };
	void setDirection(eDirection newDirection);

	inline const std::pair<int, int>& getHeadPosition() const { return partPositions_.front(); }

private:
	void move();
	std::optional<eDirection> getDirectionFromQueue();
	std::optional<eDirection> getInitialDirection();

	std::deque<std::pair<int, int>> partPositions_;
	std::pair<size_t, size_t> size_{0, 0};
	std::pair<int, int> offset_{0, 0};

	bool isChangingDirection_{false};

	eDirection direction_{eDirection::RIGHT};
	std::queue<eDirection> directionQueue_;
};