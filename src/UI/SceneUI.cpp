#include "SceneUI.hpp"

#include <SDL3_image/SDL_image.h>

#include "../Data/DataManager.hpp"

void ui::initUIText(const data::TextData& textData, ui::UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void ui::SceneUI::setCommandCallback(std::function<void(ui::UICommand)> callback)
{
	m_commandCallback = std::move(callback);
}
