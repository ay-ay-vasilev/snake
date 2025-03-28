#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "GameObjects.hpp"
#include "GameState/StartState.hpp"
#include "../Constants/Constants.hpp"

Game::Game() = default;

Game::~Game() = default;

void Game::init()
{
	auto& dataManager = constants::DataManager::getInstance();
	m_frameStep = dataManager.getConstant<int>("frame_step");

	m_gameObjects = std::make_unique<GameObjects>();
	m_gameObjects->init();

	m_state = &state::startState;
	m_state->onEnter(m_gameObjects);
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		return SDL_APP_SUCCESS;

	m_state = &m_state->handleInput(appstate, event, m_gameObjects);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::gameLoop(void* appstate, SDL_Renderer* renderer)
{
	const auto now = SDL_GetTicks();

	while((now - m_lastStep) >= m_frameStep)
	{
		update();
		m_lastStep += m_frameStep;
	}

	render(renderer);

	return SDL_APP_CONTINUE;
}

void Game::update()
{
	m_state = &m_state->update(m_gameObjects);
}

void Game::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	m_state->render(renderer, m_gameObjects);

	SDL_RenderPresent(renderer);
}