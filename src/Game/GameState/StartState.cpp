#include "StartState.hpp"
#include "../GameObjects.hpp"
#include "../../UI/UI.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "../../Constants/Constants.hpp"

state::GameState& state::StartState::update(std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->getUI()->update();
	return startState;
}

state::GameState& state::StartState::handleInput(void* appstate, SDL_Event* event, std::unique_ptr<GameObjects>& gameObjects)
{
	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_SPACE:
			return changeState(pauseState, gameObjects);
			break;
		case SDLK_R:
			return changeState(startState, gameObjects);
			break;
		default:
			return changeState(playState, gameObjects);
			break;
		}
	}

	return startState;
}

void state::StartState::render(SDL_Renderer* renderer, std::unique_ptr<GameObjects>& gameObjects)
{
	gameObjects->render(renderer);
}

void state::StartState::onEnter(std::unique_ptr<GameObjects>& gameObjects)
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

	gameObjects->reset();
	gameObjects->init();

	gameObjects->getGrid()->init(gridSize, cellSize, offset);
	gameObjects->getSnake()->init(snakePosition, cellSize, offset);
	gameObjects->getFood()->init(cellSize, offset);
	gameObjects->getUI()->init(offset);

	gameObjects->getUI()->setGameStateText("START");
}

void state::StartState::onExit(std::unique_ptr<GameObjects>& gameObjects) {}