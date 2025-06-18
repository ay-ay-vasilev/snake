#include "GameplayScene.hpp"

#include "../Game/GameObjects/GameObjects.hpp"
#include "../Game/GameState/GameState.hpp"
#include "../Game/GameState/StartState.hpp"
#include "../Game/GameState/PlayState.hpp"
#include "../Game/GameState/PauseState.hpp"
#include "../Game/GameState/LoseState.hpp"
#include "../UI/UIManager.hpp"
#include "../UI/GameplaySceneUI.hpp"

void scene::GameplayScene::init()
{
	m_states[state::StateType::eStart] = std::make_shared<state::StartState>(m_gameContext);
	m_states[state::StateType::ePlay]  = std::make_shared<state::PlayState>(m_gameContext);
	m_states[state::StateType::ePause] = std::make_shared<state::PauseState>(m_gameContext);
	m_states[state::StateType::eLose]  = std::make_shared<state::LoseState>(m_gameContext);

	auto gameObjects = std::make_shared<GameObjects>(m_gameContext);
	gameObjects->init();

	for (auto& state : m_states)
	{
		state.second->setGameObjects(gameObjects);
	}

	changeState(state::StateType::eStart);
}

void scene::GameplayScene::setSceneUI(std::unique_ptr<ui::UIManager>& uiManager)
{
	auto sceneUI = std::make_shared<ui::GameplaySceneUI>(m_gameContext, uiManager->getFontsRef());
	sceneUI->init();

	for (auto& state : m_states)
	{
		state.second->attach(sceneUI);
	}
	uiManager->setSceneUI(sceneUI);
}

void scene::GameplayScene::update()
{
	if (auto next = m_state->update())
	{
		changeState(*next);
	}
}

void scene::GameplayScene::render(SDL_Renderer* renderer)
{
	m_state->render(renderer);
}

void scene::GameplayScene::shutdown()
{
}

std::optional<scene::eSceneType> scene::GameplayScene::handleInput(void *appstate, SDL_Event* event)
{
	if (auto next = m_state->handleInput(appstate, event)) {
		changeState(*next);
	}

	return std::nullopt;
}

void scene::GameplayScene::onEnter()
{
	changeState(state::StateType::eStart);
}

void scene::GameplayScene::onExit()
{

}

void scene::GameplayScene::changeState(state::StateType newState)
{
	if (m_state)
		m_state->onExit();
	
	m_state = m_states[newState];
	m_state->onEnter();
}
