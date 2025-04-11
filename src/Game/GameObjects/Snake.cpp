#include "Snake.hpp"

#include <assert.h>
#include <algorithm>

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
	m_partPositions = initPartPositions;
	m_size = size;
	m_offset = offset;
	m_direction = getInitialDirection().value_or(eDirection::RIGHT);
}

void Snake::update()
{
	move();
}

void Snake::render(SDL_Renderer* renderer)
{
	for (auto part = m_partPositions.rbegin(); part < m_partPositions.rend(); ++part)
	{
		SDL_FRect rect;

		rect.x = m_offset.first + part->first * m_size.first;
		rect.y = m_offset.second + part->second * m_size.second;
	
		rect.w = m_size.first;
		rect.h = m_size.second;

		SDL_SetRenderDrawColor(renderer, 0, *part != m_partPositions.front() ? 100 : 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderRect(renderer, &rect);
	}
}

void Snake::setDirection(eDirection newDirection)
{
	m_directionQueue.emplace(newDirection);
};

void Snake::undoMove()
{
	assert(m_prevTail.has_value());

	m_partPositions.emplace_back(m_prevTail.value());
	m_partPositions.pop_front();
}

void Snake::grow()
{
	assert(m_prevTail.has_value());

	m_partPositions.emplace_back(m_prevTail.value());
}

const bool Snake::isSnakeCollision(const std::pair<int, int>& position) const
{
	return (std::find(m_partPositions.begin() + 1, m_partPositions.end(), position) != m_partPositions.end());
}

void Snake::move()
{
	m_prevTail = m_partPositions.back();
	m_partPositions.pop_back();
	m_direction = getDirectionFromQueue().value_or(m_direction);
	m_partPositions.emplace_front(getNextPosition());
};

std::optional<Snake::eDirection> Snake::getDirectionFromQueue()
{
	while(!m_directionQueue.empty())
	{
		eDirection directionNext = m_directionQueue.front();
		m_directionQueue.pop();
		if (isDirectionValid(directionNext, m_direction))
			return directionNext;
	}

	return std::nullopt;
}

std::optional<Snake::eDirection> Snake::getInitialDirection() const
{
	if (m_partPositions.size() > 1)
	{
		if (m_partPositions[0].first > m_partPositions[1].first) return eDirection::RIGHT;
		else if (m_partPositions[0].first < m_partPositions[1].first) return eDirection::LEFT;
		else if (m_partPositions[0].second > m_partPositions[1].second) return eDirection::DOWN;
		else if (m_partPositions[0].second < m_partPositions[1].second) return eDirection::UP;
	}

	return std::nullopt;
}

std::pair<int, int> Snake::getNextPosition() const
{
	std::pair<int, int> newPosition{ m_partPositions.front() };
	switch (m_direction)
	{
	case Snake::eDirection::UP:
		--newPosition.second;
		break;
	case Snake::eDirection::RIGHT:
		++newPosition.first;
		break;
	case Snake::eDirection::DOWN:
		++newPosition.second;
		break;
	case Snake::eDirection::LEFT:
		--newPosition.first;
		break;
	default:
		break;
	}
	return newPosition;
}