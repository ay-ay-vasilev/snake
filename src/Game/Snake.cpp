#include "Snake.hpp"

bool isDirectionValid(Snake::eDirection newDirection, Snake::eDirection curDirection)
{
	if ((newDirection == Snake::eDirection::UP && curDirection != Snake::eDirection::DOWN) ||
		(newDirection == Snake::eDirection::RIGHT && curDirection != Snake::eDirection::LEFT) ||
		(newDirection == Snake::eDirection::DOWN && curDirection != Snake::eDirection::UP) ||
		(newDirection == Snake::eDirection::LEFT && curDirection != Snake::eDirection::RIGHT))
		return true;

	return false;
}

Snake::Snake(
	std::deque<std::pair<int, int>> initPos,
	std::pair<int, int> size,
	std::pair<int, int> offset
) :
	partPositions(initPos),
	size(size),
	offset(offset)
{
	direction = getInitialDirection().value_or(eDirection::RIGHT);
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

void Snake::setDirection(eDirection newDirection)
{
	if (!isMoving) isMoving = true;
	
	directionQueue.emplace(newDirection);
};

void Snake::move()
{
	if (!isMoving) return;

	std::pair<int, int> newPosition {partPositions.front()};
	partPositions.pop_back();

	direction = getDirectionFromQueue().value_or(direction);
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

std::optional<Snake::eDirection> Snake::getDirectionFromQueue()
{
	while(!directionQueue.empty())
	{
		eDirection directionNext = directionQueue.front();
		directionQueue.pop();
		if (isDirectionValid(directionNext, direction))
			return directionNext;
	}

	return std::nullopt;
}

std::optional<Snake::eDirection> Snake::getInitialDirection()
{
	if (partPositions.size() > 1)
	{
		if (partPositions[0].first > partPositions[1].first) return eDirection::RIGHT;
		else if (partPositions[0].first < partPositions[1].first) return eDirection::LEFT;
		else if (partPositions[0].second > partPositions[1].second) return eDirection::DOWN;
		else if (partPositions[0].second < partPositions[1].second) return eDirection::UP;
	}

	return std::nullopt;
}