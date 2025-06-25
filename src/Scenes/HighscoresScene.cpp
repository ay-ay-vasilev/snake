#include "HighscoresScene.hpp"

#include "../UI/UIManager.hpp"
#include "../UI/Highscores/HighscoresSceneUI.hpp"

void scene::HighscoresScene::init()
{
	
}

void scene::HighscoresScene::setSceneUI(std::unique_ptr<ui::UIManager>& uiManager)
{
	auto sceneUI = std::make_shared<ui::HighscoresSceneUI>(m_gameContext, uiManager->getFontsRef());
	sceneUI->init();

	uiManager->setSceneUI(sceneUI);
}

void scene::HighscoresScene::update()
{

}

void scene::HighscoresScene::render(SDL_Renderer* renderer)
{

}

void scene::HighscoresScene::shutdown()
{

}

std::optional<scene::eSceneType> scene::HighscoresScene::handleInput(void *appstate, SDL_Event* event)
{
	return std::nullopt;
}

void scene::HighscoresScene::onEnter()
{

}

void scene::HighscoresScene::onExit()
{

}
