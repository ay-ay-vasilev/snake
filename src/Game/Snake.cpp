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

Snake::Snake() {}

void Snake::init(std::deque<std::pair<int, int>> initPartPositions, std::pair<size_t, size_t> size, std::pair<int, int> offset)
{
	partPositions_ = initPartPositions;
	size_ = size;
	offset_ = offset;
	direction_ = getInitialDirection().value_or(eDirection::RIGHT);
}

void Snake::update()
{
	move();
}

void Snake::render(SDL_Renderer* renderer)
{
	bool headDrawn = false;
	for (const auto& part : partPositions_)
	{
		SDL_SetRenderDrawColor(renderer, 0, headDrawn ? 100 : 255, 0, SDL_ALPHA_OPAQUE);
		if (!headDrawn) headDrawn = true;	

		SDL_FRect rect;

		rect.x = offset_.first + part.first * size_.first;
		rect.y = offset_.second + part.second * size_.second;
	
		rect.w = size_.first;
		rect.h = size_.second;

		SDL_RenderFillRect(renderer, &rect);
	}
}

void Snake::setDirection(eDirection newDirection)
{
	directionQueue_.emplace(newDirection);
};

void Snake::move()
{
	std::pair<int, int> newPosition {partPositions_.front()};
	partPositions_.pop_back();

	direction_ = getDirectionFromQueue().value_or(direction_);
	switch (direction_)
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

	partPositions_.push_front(newPosition);
};

std::optional<Snake::eDirection> Snake::getDirectionFromQueue()
{
	while(!directionQueue_.empty())
	{
		eDirection directionNext = directionQueue_.front();
		directionQueue_.pop();
		if (isDirectionValid(directionNext, direction_))
			return directionNext;
	}

	return std::nullopt;
}

std::optional<Snake::eDirection> Snake::getInitialDirection()
{
	if (partPositions_.size() > 1)
	{
		if (partPositions_[0].first > partPositions_[1].first) return eDirection::RIGHT;
		else if (partPositions_[0].first < partPositions_[1].first) return eDirection::LEFT;
		else if (partPositions_[0].second > partPositions_[1].second) return eDirection::DOWN;
		else if (partPositions_[0].second < partPositions_[1].second) return eDirection::UP;
	}

	return std::nullopt;
}