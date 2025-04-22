#include "OptionsScene.hpp"

#include "../UI/UIManager.hpp"
#include "../UI/Options/OptionsSceneUI.hpp"

void scene::OptionsScene::init()
{
	
}

void scene::OptionsScene::setSceneUI(std::unique_ptr<ui::UIManager>& uiManager)
{
	auto sceneUI = std::make_shared<ui::OptionsSceneUI>(m_gameContext, uiManager->getFontsRef());
	sceneUI->init();

	uiManager->setSceneUI(sceneUI);
}

void scene::OptionsScene::update()
{

}

void scene::OptionsScene::render(SDL_Renderer* renderer)
{

}

void scene::OptionsScene::shutdown()
{

}

std::optional<scene::eSceneType> scene::OptionsScene::handleInput(void *appstate, SDL_Event* event)
{
	return std::nullopt;
}

void scene::OptionsScene::onEnter()
{

}

void scene::OptionsScene::onExit()
{

}
