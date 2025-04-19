#include "MainMenuScene.hpp"

#include "../UI/UIManager.hpp"
#include "../UI/MainMenu/MainMenuSceneUI.hpp"

void scene::MainMenuScene::init()
{
	
}

void scene::MainMenuScene::setSceneUI(std::unique_ptr<ui::UIManager>& uiManager)
{
	auto sceneUI = std::make_shared<ui::MainMenuSceneUI>();
	sceneUI->init();

	uiManager->setSceneUI(sceneUI);
}

void scene::MainMenuScene::update()
{

}

void scene::MainMenuScene::render(SDL_Renderer* renderer)
{

}

void scene::MainMenuScene::shutdown()
{

}

std::optional<scene::eSceneType> scene::MainMenuScene::handleInput(void *appstate, SDL_Event* event)
{
	return std::nullopt;
}

void scene::MainMenuScene::onEnter()
{

}

void scene::MainMenuScene::onExit()
{

}
