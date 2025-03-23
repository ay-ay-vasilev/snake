#include "GameState.hpp"

#include "../GameObjects.hpp"
#include "../Grid.hpp"
#include "../Snake.hpp"
#include "../../UI/UI.hpp"
#include "../../Constants/Constants.hpp"

GameState& GameState::changeState(GameState& currentState, GameState& newState, std::unique_ptr<GameObjects>& gameObjects)
{
	currentState.onExit(gameObjects);
	newState.onEnter(gameObjects);
	return newState;
}

bool PlayState::checkCollision(std::unique_ptr<Grid>& grid, const std::pair<int, int>& position) const
{
	return grid->isCollision(position);
}

GameState& PlayState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->grid->update();
	gameObjects->snake->update();
	gameObjects->ui->update();

	const auto& snakePos = gameObjects->snake->getHeadPosition();
	if (checkCollision(gameObjects->grid, snakePos))
	{
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

GameState& PauseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->update();
	return pauseState;
}

GameState& PauseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return changeState(pauseState, playState, gameObjects);
			break;
		case SDLK_R:
			return changeState(pauseState, startState, gameObjects);
			break;
		default:
			break;
		}
	}

	return pauseState;
}

void PauseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->setGameStateText("PAUSED");
}

void PauseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}

GameState& StartState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->update();
	return startState;
}

GameState& StartState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return changeState(startState, pauseState, gameObjects);
			break;
		case SDLK_R:
			return changeState(startState, startState, gameObjects);
			break;
		default:
			return changeState(startState, playState, gameObjects);
			break;
		}
	}

	return startState;
}

void StartState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	auto& dataManager = constants::DataManager::getInstance();

	const auto windowWidth = dataManager.getConstant<int>("window_width");
	const auto windowHeight = dataManager.getConstant<int>("window_height");
	const auto gridWH = dataManager.getConstant<int>("grid_size");
	const auto cellWH = dataManager.getConstant<int>("cell_size");

	const auto gridWidth = gridWH * cellWH;
	const auto gridHeight = gridWH * cellWH;
	const std::pair<int, int> offset =
	{
		(windowWidth - gridWidth) / 2,
		(windowHeight - gridHeight) / 2
	};
	const std::pair<int, int> gridSize = { gridWH, gridWH };
	const std::pair<int, int> cellSize = { cellWH, cellWH };
	const std::deque<std::pair<int, int>> snakePosition = {{4, 4},{3, 4},{2, 4},{1, 4}};

	gameObjects->grid.reset();
	gameObjects->snake.reset();
	gameObjects->ui.reset();

	gameObjects->grid = std::make_unique<Grid>();
	gameObjects->snake = std::make_unique<Snake>();
	gameObjects->ui = std::make_unique<UI>();

	gameObjects->grid->init(gridSize, cellSize, offset);
	gameObjects->snake->init(snakePosition, cellSize, offset);
	gameObjects->ui->init(offset);

	gameObjects->ui->setGameStateText("START");
}

void StartState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}

GameState& LoseState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->update();
	return loseState;
}

GameState& LoseState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		default:
			return changeState(loseState, startState, gameObjects);
			break;
		}
	}

	return loseState;
}

void LoseState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->ui->setGameStateText("LOSE");
}

void LoseState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}