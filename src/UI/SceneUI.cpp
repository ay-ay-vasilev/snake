#include "SceneUI.hpp"

#include <SDL3_image/SDL_image.h>

#include "../Constants/Constants.hpp"

void ui::initUIText(const constants::TextData& textData, ui::UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void ui::SceneUI::setSceneUIData(std::shared_ptr<SceneUIData> sceneUIData)
{
	m_sceneUIData = sceneUIData;
}

void ui::SceneUI::setCommandCallback(std::function<void(ui::UICommand)> callback)
{
	m_commandCallback = std::move(callback);
}
