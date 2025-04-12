#include "UI.hpp"

#include "../Constants/Constants.hpp"
#include <iostream>

void ui::initUIText(const constants::TextData& textData, ui::UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void ui::UI::init(SDL_Window* window, SDL_Renderer* renderer)
{
	auto& dataManager = constants::DataManager::getInstance();

	const auto windowWidth = dataManager.getConstant<int>("window_width");
	const auto windowHeight = dataManager.getConstant<int>("window_height");
	const auto gridWH = dataManager.getConstant<int>("grid_size");
	const auto cellWH = dataManager.getConstant<int>("cell_size");

	const auto gridWidth = gridWH * cellWH;
	const auto gridHeight = gridWH * cellWH;
	const std::pair<int, int> offset =
	{
		(windowWidth - gridWidth) / 2,
		(windowHeight - gridHeight) / 2
	};

	m_offset = offset;
	m_windowSize = {windowWidth, windowHeight};
}

void ui::UI::handleInput(void* appstate, SDL_Event* event)
{
}

void ui::UI::update()
{
}

void ui::UI::preRender(SDL_Renderer* renderer)
{
}

void ui::UI::postRender(SDL_Renderer* renderer)
{
}

void ui::UI::shutdown()
{
}

void ui::UI::renderUIText(SDL_Renderer* renderer, const UIText& uiText)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, uiText.scale, uiText.scale);
	SDL_RenderDebugText(renderer,
		(uiText.x + m_offset.first) / uiText.scale,
		(uiText.y + m_offset.second) / uiText.scale,
		uiText.text.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}
