#include "SceneUI.hpp"

#include "../Constants/Constants.hpp"

void ui::initUIText(const constants::TextData& textData, ui::UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void ui::SceneUI::init()
{
}

void ui::SceneUI::handleInput(void* appstate, SDL_Event* event)
{
}

void ui::SceneUI::update()
{
}

void ui::SceneUI::render(SDL_Renderer* renderer, int windowFlags) 
{
}

void ui::SceneUI::setSceneUIData(std::shared_ptr<SceneUIData> sceneUIData)
{
	m_sceneUIData = sceneUIData;
}
