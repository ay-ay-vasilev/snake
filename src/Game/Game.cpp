#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "GameObjects.hpp"
#include "GameState/GameState.hpp"
#include "GameState/StartState.hpp"
#include "GameState/PlayState.hpp"
#include "GameState/PauseState.hpp"
#include "GameState/LoseState.hpp"
#include "../UI/UI.hpp"
#include "../Constants/Constants.hpp"

static ui::UI uiManager;

Game::Game() = default;

Game::~Game()
{
};

void Game::init(SDL_Window* window, SDL_Renderer* renderer)
{
	m_states[state::StateType::eStart] = std::make_shared<state::StartState>();
	m_states[state::StateType::ePlay]  = std::make_shared<state::PlayState>();
	m_states[state::StateType::ePause] = std::make_shared<state::PauseState>();
	m_states[state::StateType::eLose]  = std::make_shared<state::LoseState>();

	for (auto& state : m_states)
		state.second->Attach(&uiManager);

	auto& dataManager = constants::DataManager::getInstance();
	m_frameStep = dataManager.getConstant<int>("frame_step");

	uiManager.init(window, renderer);

	m_gameObjects = std::make_unique<GameObjects>();
	m_gameObjects->init();

	m_state = getState(state::StateType::eStart);
	m_state->Attach(&uiManager);
	m_state->onEnter(m_gameObjects);
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		return SDL_APP_SUCCESS;

	if (auto newStateType = m_state->handleInput(appstate, event, m_gameObjects); newStateType != m_state->getStateType())
	{
		changeState(getState(newStateType), m_gameObjects);
	}

	uiManager.handleInput(appstate, event);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::gameLoop(void* appstate, SDL_Renderer* renderer)
{
	const auto now = SDL_GetTicks();

	while((now - m_lastStep) >= m_frameStep)
	{
		update();
		uiManager.update();
		m_lastStep += m_frameStep;
	}

	uiManager.preRender(renderer);
	render(renderer);
	uiManager.postRender(renderer);

	return SDL_APP_CONTINUE;
}

void Game::shutdown()
{
	uiManager.shutdown();
}

void Game::update()
{
	if (auto newStateType = m_state->update(m_gameObjects); newStateType != m_state->getStateType())
	{
		changeState(getState(newStateType), m_gameObjects);
	}
}

void Game::render(SDL_Renderer* renderer)
{
	m_state->render(renderer, m_gameObjects);
}

void Game::changeState(std::shared_ptr<state::GameState>& newState, std::unique_ptr<GameObjects>& gameObjects)
{
	if (m_state)
		m_state->onExit(gameObjects);
	
	newState->onEnter(gameObjects);
	m_state = newState;
}

std::shared_ptr<state::GameState>& Game::getState(state::StateType type)
{
	return m_states[type];
}