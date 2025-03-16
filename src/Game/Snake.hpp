#pragma once

#include <SDL3_image/SDL_image.h>
#include <deque>

class Snake
{
public:
	Snake(
		std::deque<std::pair<int, int>> initPos,
		std::pair<int, int> size,
		std::pair<int, int> offset
	);

	enum class eDirection
	{
		UP = 0,
		RIGHT,
		DOWN,
		LEFT
	};

	void init();
	void update();
	void render(SDL_Renderer* renderer);

	inline const int getDirection() const { return static_cast<int>(direction); };
	void setDirection(int newDirection);

private:
	void move();

	std::deque<std::pair<int, int>> partPositions;
	std::pair<int, int> size;
	std::pair<int, int> offset;

	bool isMoving{false};
	eDirection direction;
};