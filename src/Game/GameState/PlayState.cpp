#include "PlayState.hpp"
#include "../GameObjects.hpp"
#include "LoseState.hpp"
#include "PauseState.hpp"
#include "StartState.hpp"

state::StateType state::PlayState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	const auto& grid = gameObjects->getGrid();
	const auto& snake = gameObjects->getSnake();
	const auto& food = gameObjects->getFood();

	gameObjects->update();

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
		CreateMessage(ObserverMessageType::eScore, 1);
		snake->grow();
	}

	if (food->getFoodCount() < 1)
		food->spawnFood(grid->getGridSize(), {snake->getPartPositions()});

	return state::StateType::ePlay;
}

void state::PlayState::render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->render(renderer);
}

state::StateType state::PlayState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
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
			gameObjects->getSnake()->setDirection(Snake::eDirection::UP);
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			gameObjects->getSnake()->setDirection(Snake::eDirection::RIGHT);
			break;
		case SDLK_S:
		case SDLK_DOWN:
			gameObjects->getSnake()->setDirection(Snake::eDirection::DOWN);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			gameObjects->getSnake()->setDirection(Snake::eDirection::LEFT);
			break;
		
		default:
			break;
		}
	}

	return state::StateType::ePlay;
}

void state::PlayState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	CreateMessage(ObserverMessageType::eGameState, std::string("PLAY"));
}

void state::PlayState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}