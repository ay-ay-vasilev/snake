#include "PlayState.hpp"
#include "../GameObjects.hpp"
#include "../Grid.hpp"
#include "../Snake.hpp"
#include "../../UI/UI.hpp"
#include "LoseState.hpp"
#include "PauseState.hpp"
#include "StartState.hpp"

bool checkCollision(const std::unique_ptr<Grid>& grid, const std::pair<int, int>& position)
{
	return grid->isCollision(position);
}

GameState& PlayState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	const auto& grid = gameObjects->grid;
	const auto& snake = gameObjects->snake;

	grid->update();
	snake->update();
	gameObjects->ui->update();

	const auto& snakePos = snake->getHeadPosition();
	if (checkCollision(grid, snakePos))
	{
		snake->undoMove();
		return changeState(playState, loseState, gameObjects);
	}

	return playState;
}

GameState& PlayState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return changeState(playState, pauseState, gameObjects);
			break;
		case SDLK_R:
			return changeState(playState, startState, gameObjects);
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
			gameObjects->snake->setDirection(Snake::eDirection::UP);
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			gameObjects->snake->setDirection(Snake::eDirection::RIGHT);
			break;
		case SDLK_S:
		case SDLK_DOWN:
			gameObjects->snake->setDirection(Snake::eDirection::DOWN);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			gameObjects->snake->setDirection(Snake::eDirection::LEFT);
			break;
		
		default:
			break;
		}
	}

	return playState;
}

void PlayState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->setGameStateText("PLAY");
}

void PlayState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}