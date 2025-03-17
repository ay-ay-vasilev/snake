#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "Grid.hpp"
#include "Snake.hpp"
#include "UI.hpp"
#include "Constants.hpp"

Game::Game() = default;

Game::~Game() = default;

void Game::init()
{
	const auto gridWidth = constants::GRID_SIZE * constants::CELL_SIZE;
	const auto gridHeight = constants::GRID_SIZE * constants::CELL_SIZE;
	const std::pair<int, int> offset =
	{
		(constants::WINDOW_WIDTH - gridWidth) / 2,
		(constants::WINDOW_HEIGHT - gridHeight) / 2
	};
	const std::pair<int, int> gridSize = {constants::GRID_SIZE, constants::GRID_SIZE};
	const std::pair<int, int> cellSize = {constants::CELL_SIZE, constants::CELL_SIZE};

	grid = std::make_unique<Grid>(gridSize, cellSize, offset);
	grid->init();

	const std::deque<std::pair<int, int>> snakePosition = {{4, 4},{3, 4},{2, 4},{1, 4}};

	snake = std::make_unique<Snake>(snakePosition, cellSize, offset);

	ui = std::make_unique<UI>();
	ui->init();
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT || (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE))
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_DOWN)
	{
		switch (event->key.key)
		{
		case SDLK_W:
		case SDLK_UP:
			snake->setDirection(Snake::eDirection::UP);
			break;
		case SDLK_D:
		case SDLK_RIGHT:
			snake->setDirection(Snake::eDirection::RIGHT);
			break;
		case SDLK_S:
		case SDLK_DOWN:
			snake->setDirection(Snake::eDirection::DOWN);
			break;
		case SDLK_A:
		case SDLK_LEFT:
			snake->setDirection(Snake::eDirection::LEFT);
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

	while((now - lastStep) >= constants::FRAME_STEP)
	{
		update();
		lastStep += constants::FRAME_STEP;
	}

	render(renderer);

	return SDL_APP_CONTINUE;
}

void Game::update()
{
	snake->update();
	grid->update();
	ui->update();

	ui->setDirection(snake->getDirection());
}

void Game::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	grid->render(renderer);
	snake->render(renderer);
	ui->render(renderer);

	SDL_RenderPresent(renderer);
}