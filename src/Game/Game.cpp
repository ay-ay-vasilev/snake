#include "Game.hpp"

#include <SDL3_image/SDL_image.h>

#include "../Scenes/Scene.hpp"
#include "../Scenes/GameplayScene.hpp"
#include "../Scenes/MainMenuScene.hpp"
#include "../Scenes/OptionsScene.hpp"
#include "../Scenes/HighscoresScene.hpp"
#include "../Scenes/SaveHighscoreScene.hpp"

#include "GameContext.hpp"
#include "../UI/UIManager.hpp"

Game::~Game() = default;

void Game::init(SDL_Window* window, SDL_Renderer* renderer)
{
	m_uiManager = std::make_unique<ui::UIManager>(m_gameContext);
	m_uiManager->init(window, renderer);

	m_scenes[scene::eSceneType::Gameplay] = std::make_shared<scene::GameplayScene>(m_gameContext);
	m_scenes[scene::eSceneType::MainMenu]  = std::make_shared<scene::MainMenuScene>(m_gameContext);
	m_scenes[scene::eSceneType::Options] = std::make_shared<scene::OptionsScene>(m_gameContext);
	m_scenes[scene::eSceneType::Highscores] = std::make_shared<scene::HighscoresScene>(m_gameContext);
	m_scenes[scene::eSceneType::SaveHighscore] = std::make_shared<scene::SaveHighscoreScene>(m_gameContext);
	
	for (auto& scene : m_scenes)
		scene.second->init();

	auto& optionsManager = m_gameContext->getOptionsManager();
	m_frameStep = optionsManager->getGameSpeed().frameStep;

	changeScene(scene::eSceneType::MainMenu);
}

SDL_AppResult Game::handleInput(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	if (auto next = m_currentScene->handleInput(appstate, event))
	{
		changeScene(*next);
	}

	m_uiManager->handleInput(appstate, event);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::gameLoop(void* appstate, SDL_Renderer* renderer)
{
	const auto now = SDL_GetTicks();

	auto& optionsManager = m_gameContext->getOptionsManager();
	m_frameStep = optionsManager->getGameSpeed().frameStep;

	while((now - m_lastStep) >= m_frameStep)
	{
		if (auto appResult = update())
			return *appResult;
		m_lastStep += m_frameStep;
	}
	render(renderer);

	return SDL_APP_CONTINUE;
}

void Game::shutdown()
{
	for (auto& scene : m_scenes)
		scene.second->shutdown();
}

std::optional<SDL_AppResult> Game::update()
{
	m_uiManager->update();
	m_currentScene->update();

	if (auto command = m_uiManager->pollCommand())
	{
		if (command->type == ui::eUICommandType::ChangeScene)
		{
			changeScene(std::any_cast<scene::eSceneType>(command->value));
		}
		else if (command->type == ui::eUICommandType::QuitGame)
		{
			return SDL_APP_SUCCESS;
		}
	}

	return std::nullopt;
}

void Game::render(SDL_Renderer* renderer)
{
	m_uiManager->preRender(renderer);
	m_currentScene->render(renderer);
	m_uiManager->postRender(renderer);
}

void Game::changeScene(scene::eSceneType type)
{
	if (m_currentScene) {
		m_currentScene->onExit();
	}

	m_currentScene = m_scenes[type];
	m_currentScene->onEnter();
	m_currentScene->setSceneUI(m_uiManager);
}
