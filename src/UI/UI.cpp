#include "UI.hpp"
#include "../Constants/Constants.hpp"

void initUIText(const constants::TextData& textData, UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void UI::init(std::pair<int, int> offset)
{
	auto& dataManager = constants::DataManager::getInstance();

	const auto& scoreTextData = dataManager.getConstant<constants::TextData>("score_text");
	const auto& gameStateTextData = dataManager.getConstant<constants::TextData>("game_state_text");
	const auto& debugTextData = dataManager.getConstant<constants::TextData>("debug_text");

	initUIText(scoreTextData, m_scoreText);
	initUIText(gameStateTextData, m_gameStateText);
	initUIText(debugTextData, m_debugText);

	m_offset = offset;
	m_scoreText.text = "Score: " + std::to_string(m_score);
	m_gameStateText.text = "START";
	m_debugText.text = "DEBUG";
}

void UI::update()
{
	m_scoreText.text = "Score: " + std::to_string(m_score);
}

void UI::render(SDL_Renderer* renderer)
{
	renderUIText(renderer, m_scoreText);
	renderUIText(renderer, m_gameStateText);
	renderUIText(renderer, m_debugText);
}

void UI::renderUIText(SDL_Renderer* renderer, const UIText& uiText)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, uiText.scale, uiText.scale);
	SDL_RenderDebugText(renderer,
		(uiText.x + m_offset.first) / uiText.scale,
		(uiText.y + m_offset.second) / uiText.scale,
		uiText.text.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}

void UI::addScore(int value)
{
	m_score += value;
}

void UI::setGameStateText(const std::string_view& text)
{
	m_gameStateText.text = text;
}

void UI::setDebugText(const std::string_view& text)
{
	m_debugText.text = text;
}