#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "Grid.hpp"
#include "Snake.hpp"
#include "../UI/UI.hpp"
#include "../Constants/Constants.hpp"

Game::Game() = default;

Game::~Game() = default;

void Game::init()
{
	reset();
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_UP)
	{
		switch (event->key.key)
		{
		case SDLK_ESCAPE:
			return SDL_APP_SUCCESS;
			break;
		case SDLK_SPACE:
			isPaused_ = !isPaused_;
			ui_->setPaused(isPaused_);
			break;
		case SDLK_R:
			reset();
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
			snake_->setDirection(Snake::eDirection::UP);
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			snake_->setDirection(Snake::eDirection::RIGHT);
			break;
		case SDLK_S:
		case SDLK_DOWN:
			snake_->setDirection(Snake::eDirection::DOWN);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			snake_->setDirection(Snake::eDirection::LEFT);
			break;
		
		default:
			break;
		}

		return SDL_APP_CONTINUE;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::gameLoop(void* appstate, SDL_Renderer* renderer)
{
	const auto now = SDL_GetTicks();

	while((now - lastStep_) >= frameStep_)
	{
		update();
		lastStep_ += frameStep_;
	}

	render(renderer);

	return SDL_APP_CONTINUE;
}

void Game::update()
{
	if (!isPaused_)
	{
		grid_->update();
		snake_->update();

		const auto& snakePos = snake_->getHeadPosition();
		if (checkCollision(snakePos))
			reset();
	}

	ui_->update();
}

void Game::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	grid_->render(renderer);
	snake_->render(renderer);
	ui_->render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::reset()
{
	auto& dataManager = constants::DataManager::getInstance();

	const auto windowWidth = dataManager.getConstant<int>("window_width");
	const auto windowHeight = dataManager.getConstant<int>("window_height");
	const auto gridWH = dataManager.getConstant<int>("grid_size");
	const auto cellWH = dataManager.getConstant<int>("cell_size");

	frameStep_ = dataManager.getConstant<int>("frame_step");

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

	grid_.reset();
	snake_.reset();
	ui_.reset();

	grid_ = std::make_unique<Grid>();
	snake_ = std::make_unique<Snake>();
	ui_ = std::make_unique<UI>();

	grid_->init(gridSize, cellSize, offset);
	snake_->init(snakePosition, cellSize, offset);
	ui_->init(offset);
}

bool Game::checkCollision(const std::pair<int, int>& position) const
{
	return grid_->isCollision(position);
}