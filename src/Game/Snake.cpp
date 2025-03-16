#include "Snake.hpp"

Snake::Snake(
	std::deque<std::pair<int, int>> initPos,
	std::pair<int, int> size,
	std::pair<int, int> offset
) :
	partPositions(initPos),
	size(size),
	offset(offset)
{
	direction = eDirection::RIGHT;
	if (partPositions.size() > 1)
	{
		if (partPositions[0].first > partPositions[1].first)
			direction = eDirection::RIGHT;
		else if (partPositions[0].first < partPositions[1].first)
			direction = eDirection::LEFT;
		else if (partPositions[0].second > partPositions[1].second)
			direction = eDirection::DOWN;
		else if (partPositions[0].second < partPositions[1].second)
			direction = eDirection::UP;
	}
}

void Snake::init() {}

void Snake::update()
{
	move();
}

void Snake::render(SDL_Renderer* renderer)
{
	bool headDrawn = false;
	for (const auto& part : partPositions)
	{
		SDL_SetRenderDrawColor(renderer, 0, headDrawn ? 100 : 255, 0, SDL_ALPHA_OPAQUE);
		if (!headDrawn) headDrawn = true;	

		SDL_FRect rect;

		rect.x = offset.first + part.first * size.first;
		rect.y = offset.second + part.second * size.second;
	
		rect.w = size.first;
		rect.h = size.second;

		SDL_RenderFillRect(renderer, &rect);
	}
}

void Snake::setDirection(int newDirection)
{
	if (!isMoving) isMoving = true;

	const auto convertedDirection = static_cast<eDirection>(newDirection);

	if ((convertedDirection == eDirection::UP && direction != eDirection::DOWN) ||
		(convertedDirection == eDirection::RIGHT && direction != eDirection::LEFT) ||
		(convertedDirection == eDirection::DOWN && direction != eDirection::UP) ||
		(convertedDirection == eDirection::LEFT && direction != eDirection::RIGHT))
	{
		direction = convertedDirection;
	}
	
};

void Snake::move()
{
	if (!isMoving) return;

	std::pair<int, int> newPosition {partPositions.front()};
	partPositions.pop_back();

	switch (direction)
	{
	case eDirection::UP:
		--newPosition.second;
		break;
	case eDirection::RIGHT:
		++newPosition.first;
		break;
	case eDirection::DOWN:
		++newPosition.second;
		break;
	case eDirection::LEFT:
		--newPosition.first;
		break;
	default:
		break;
	}

	partPositions.push_front(newPosition);
};