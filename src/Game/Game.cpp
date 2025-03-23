#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "GameObjects.hpp"
#include "GameState/GameState.hpp"
#include "Grid.hpp"
#include "Snake.hpp"
#include "../UI/UI.hpp"
#include "../Constants/Constants.hpp"

Game::Game() = default;

Game::~Game() = default;

void Game::init()
{
	auto& dataManager = constants::DataManager::getInstance();
	frameStep_ = dataManager.getConstant<int>("frame_step");

	gameObjects_ = std::make_unique<GameObjects>();

	gameObjects_->grid = std::make_unique<Grid>();
	gameObjects_->snake = std::make_unique<Snake>();
	gameObjects_->ui = std::make_unique<UI>();

	state_ = &startState;
	state_->onEnter(gameObjects_);
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		return SDL_APP_SUCCESS;

	state_ = &state_->handleInput(appstate, event, gameObjects_);

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
	state_ = &state_->update(gameObjects_);
}

void Game::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	gameObjects_->grid->render(renderer);
	gameObjects_->snake->render(renderer);
	gameObjects_->ui->render(renderer);

	SDL_RenderPresent(renderer);
}