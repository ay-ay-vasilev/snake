#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "../Scenes/Scene.hpp"
#include "../Scenes/GameplayScene.hpp"
#include "../Scenes/MainMenuScene.hpp"
#include "../Scenes/OptionsScene.hpp"

#include "../UI/UI.hpp"
#include "../Constants/Constants.hpp"

static ui::UI uiManager;

Game::Game() = default;

Game::~Game() = default;

void Game::init(SDL_Window* window, SDL_Renderer* renderer)
{
	uiManager.init(window, renderer);

	m_scenes[scene::SceneType::eGameplay] = std::make_shared<scene::GameplayScene>();
	m_scenes[scene::SceneType::eMainMenu]  = std::make_shared<scene::MainMenuScene>();
	m_scenes[scene::SceneType::eOptions] = std::make_shared<scene::OptionsScene>();
	
	for (auto& scene : m_scenes)
		scene.second->init(uiManager);

	auto& dataManager = constants::DataManager::getInstance();
	m_frameStep = dataManager.getConstant<int>("frame_step");

	changeScene(scene::SceneType::eGameplay);
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	if (event->key.type == SDL_EVENT_KEY_UP && event->key.key == SDLK_ESCAPE)
		return SDL_APP_SUCCESS;

	if (auto next = m_currentScene->handleInput(appstate, event))
	{
		changeScene(*next);
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
	m_currentScene->update();
}

void Game::render(SDL_Renderer* renderer)
{
	m_currentScene->render(renderer);
}

void Game::changeScene(scene::SceneType type)
{
	if (m_currentScene) {
		m_currentScene->onExit();
	}

	m_currentScene = m_scenes[type];
	m_currentScene->onEnter();
}