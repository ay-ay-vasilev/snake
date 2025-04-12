#include "PlayState.hpp"
#include "../GameObjects/GameObjects.hpp"
#include "LoseState.hpp"
#include "PauseState.hpp"
#include "StartState.hpp"

std::optional<state::StateType> state::PlayState::update()
{
	const auto& grid = m_gameObjects->getGrid();
	const auto& snake = m_gameObjects->getSnake();
	const auto& food = m_gameObjects->getFood();

	m_gameObjects->update();

	const auto& snakePos = snake->getHeadPosition();
	if (grid->isWallCollision(snakePos))
	{
		return state::StateType::eLose;
	}

	if (snake->isSnakeCollision(snakePos))
	{
		return state::StateType::eLose;
	}

	if (food->tryProcessFoodCollision(snakePos))
	{
		createMessage(ObserverMessageType::eAddScore, 1);
		snake->grow();
	}

	if (food->getFoodCount() < 1)
		food->spawnFood(grid->getGridSize(), {snake->getPartPositions()});

	return std::nullopt;
}

void state::PlayState::render(SDL_Renderer* renderer)
{
	m_gameObjects->render(renderer);
}

std::optional<state::StateType> state::PlayState::handleInput(void* appstate, SDL_Event* event)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return state::StateType::ePause;
			break;
		case SDLK_R:
			return state::StateType::eStart;
			break;
		default:
			break;
		}
	}

	if (event->key.type == SDL_EVENT_KEY_DOWN)
	{
		switch (event->key.key)
		{
		case SDLK_W:
		case SDLK_UP:
			m_gameObjects->getSnake()->setDirection(Snake::eDirection::UP);
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			m_gameObjects->getSnake()->setDirection(Snake::eDirection::RIGHT);
			break;
		case SDLK_S:
		case SDLK_DOWN:
			m_gameObjects->getSnake()->setDirection(Snake::eDirection::DOWN);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			m_gameObjects->getSnake()->setDirection(Snake::eDirection::LEFT);
			break;
		
		default:
			break;
		}
	}

	return std::nullopt;
}

void state::PlayState::onEnter()
{
	createMessage(ObserverMessageType::eGameState, std::string("PLAY"));
}

void state::PlayState::onExit() {}
