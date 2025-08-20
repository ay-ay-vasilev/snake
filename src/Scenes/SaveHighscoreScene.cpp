#include "SaveHighscoreScene.hpp"

#include "../UI/UIManager.hpp"
#include "../UI/SaveHighscore/SaveHighscoreSceneUI.hpp"

void scene::SaveHighscoreScene::init()
{

}

void scene::SaveHighscoreScene::setSceneUI(std::unique_ptr<ui::UIManager>& uiManager)
{
	auto sceneUI = std::make_shared<ui::SaveHighscoreSceneUI>(m_gameContext, uiManager->getFontsRef());
	sceneUI->init();

	uiManager->setSceneUI(sceneUI);
}

void scene::SaveHighscoreScene::update()
{

}

void scene::SaveHighscoreScene::render(SDL_Renderer* renderer)
{

}

void scene::SaveHighscoreScene::shutdown()
{

}

std::optional<scene::eSceneType> scene::SaveHighscoreScene::handleInput(void *appstate, SDL_Event* event)
{
	return std::nullopt;
}

void scene::SaveHighscoreScene::onEnter()
{

}

void scene::SaveHighscoreScene::onExit()
{

}
