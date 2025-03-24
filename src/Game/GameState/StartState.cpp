#include "StartState.hpp"
#include "../GameObjects.hpp"
#include "../Grid.hpp"
#include "../Snake.hpp"
#include "../../UI/UI.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "../../Constants/Constants.hpp"

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